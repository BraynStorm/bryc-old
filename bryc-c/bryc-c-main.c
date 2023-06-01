#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <assert.h>

#include "alloc.h"

internal char*
read_file(char const* path)
{
    char* data = 0;
    FILE* file = 0;

    if (!fopen_s(&file, path, "r")) {
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        fseek(file, 0, SEEK_SET);
        data = calloc(1, size);
        size = fread(data, 1, size, file);
        data[size] = 0;
        fclose(file);
    }

    return data;
}

struct lex_state
{
    char const* filepath;
    char const* src_text;
    size_t src_head;
    size_t src_size;

    struct token* tokens;
    size_t n_tokens;
    size_t cap_tokens;
};

// clang-format off
#define TOKENS_SINGLE_CHAR  \
    TOKEN(semicolon, ';')   \
    TOKEN(paren_l,   '(')   \
    TOKEN(paren_r,   ')')   \
    TOKEN(bracket_l, '[')   \
    TOKEN(bracket_r, ']')   \
    TOKEN(brace_l,   '{')   \
    TOKEN(brace_r,   '}')   \
    TOKEN(dot,       '.')   \
    TOKEN(hash,      '#')   \
    TOKEN(equals,    '=')   \
    TOKEN(plus,      '+')   \
    TOKEN(minus,     '-')   \
    TOKEN(star,      '*')   \
    TOKEN(slash,     '/')   \
    TOKEN(colon,     ':')   \
    TOKEN(question,  '?')   \
    TOKEN(hat,       '^')   \
    TOKEN(amp,       '&')   \
    TOKEN(pipe,      '|')   \
    TOKEN(at,        '@')   \
    /**/
// clang-format on

/* TODO: Make the lexer have a second pass producing these. */
// #define TOKENS_MULTI_CHAR    \
//     TOKEN(bool_eq, "==")     \
//     TOKEN(bool_neq, "!=")    \
//     TOKEN(bool_gt, ">")      \
//     TOKEN(bool_lt, "<")      \
//     TOKEN(bool_gte, ">=")    \
//     TOKEN(bool_lte, "<=")    \
//     TOKEN(bool_and, "&&")    \
//     TOKEN(bool_or, "||")     \
//     TOKEN(shift_left, "<<")  \
//     TOKEN(shift_right, ">>") \
//     /**/

#define TOKENS_COMPOUND  \
    TOKEN(identifier, {  \
        int pos;         \
        int length;      \
    })                   \
    TOKEN(literal_int, { \
        int pos;         \
        int length;      \
    })


#define TOKENS      \
    TOKENS_COMPOUND \
    TOKENS_SINGLE_CHAR

enum token_type
{
#define TOKEN(name, ...) tok_##name,
    TOKENS
#undef TOKEN
};


#define TOKEN(name, ...) \
    struct tok_##name    \
    {                    \
        int pos;         \
    };
TOKENS_SINGLE_CHAR
#undef TOKEN

#define TOKEN(name, ...) struct tok_##name __VA_ARGS__;
TOKENS_COMPOUND
#undef TOKEN

struct token
{
    enum token_type type;
    union
    {
#define TOKEN(name, ...) struct tok_##name name;
        TOKENS
#undef TOKEN
    };
};


char const* token_names[] = {
#define TOKEN(name, ...) #name,
    TOKENS
#undef TOKEN
};

char const*
token_name(enum token_type t)
{
    return token_names[t];
}

struct token_location
{
    int line;
    int col;
};

/* Gets the location in the file given a token.

PERF:
    SUPER SLOW. Fix this by having a table for the lines?
    Like:
        ...
        { line 6: start=10, end=33}
        { line 7: start=33, end=293}
        ...
*/
internal struct token_location
lex_token_location(char const* source_text, int pos)
{
    assert(pos < strlen(source_text));

    struct token_location loc = { 1, 1 };
    for (int i = 0; i < pos; ++i) {
        char c = source_text[i];

        if (c == '\n') {
            loc.line += 1;
            loc.col = 1;
        } else {
            loc.col += 1;
        }
    }

    return loc;
}

internal void
debug_lex_dump_tokens_stringy(struct lex_state* _state, int pos, int length)
{
    printf(" pos=%4d, length=%4d, value=", pos, length);
    for (int j = pos; j < length + pos; ++j) {
        fputc(_state->src_text[j], stdout);
    }
    fputs("|END", stdout);
}

internal void
debug_lex_dump_tokens(struct lex_state state)
{
    puts("---------------- TOKENS ----------------");

    for (int i = 0; i < state.n_tokens; ++i) {
        struct token tok = state.tokens[i];

        struct token_location loc = lex_token_location(
            state.src_text,
            tok.semicolon.pos
        );

        printf(
            "%s:%d:%-3d | %12s | ",
            state.filepath,
            loc.line,
            loc.col,
            token_name(tok.type)
        );

        switch (tok.type) {
            case tok_identifier:
                debug_lex_dump_tokens_stringy(
                    &state,
                    tok.identifier.pos,
                    tok.identifier.length
                );
                break;
            case tok_literal_int:
                debug_lex_dump_tokens_stringy(
                    &state,
                    tok.literal_int.pos,
                    tok.literal_int.length
                );
                break;
            case tok_semicolon:
            case tok_paren_l:
            case tok_paren_r:
            case tok_bracket_l:
            case tok_bracket_r:
            case tok_brace_l:
            case tok_brace_r:
            case tok_hash:
            case tok_equals:
            case tok_plus:
            case tok_minus:
            case tok_star:
            case tok_slash:
            case tok_colon:
            case tok_question:
            case tok_hat:
            case tok_amp:
            case tok_pipe:
            case tok_at:
            case tok_dot: break;
        }
        printf("\n");
    }
    puts("-------------- END TOKENS --------------");
}

internal struct lex_state
lex(char const* path, char const* source_text)
{
    int const max_tokens = 1024;
    struct lex_state state = {
        .filepath = path,
        .src_text = source_text,
        .src_head = 0,
        .src_size = strlen(source_text),

        .tokens = calloc(max_tokens, sizeof(struct token)),
        0,
        max_tokens,
    };

#define LEX_CURRENT_TOKEN (state.tokens[state.n_tokens])
#define LEX_LAST_TOKEN (state.tokens[state.n_tokens - 1])
#define LEX_PUSH_TOKEN   \
    state.n_tokens += 1; \
    assert(state.n_tokens < state.cap_tokens)

    bool last_was_whitespace = 1;

    while (state.src_head < state.src_size) {
        char c = state.src_text[state.src_head];
        switch (c) {
            case '\0': break;

            case ' ':
            case '\n':
            case '\r': {
                last_was_whitespace = 1;
                ++state.src_head;
                continue;
            }

            case '\'':
            case '"':
                /*TODO(bozho2):
                    Add string and character support.
                */
                exit(1);
                break;

            case '_':
            case 'a' ... 'z':
            case 'A' ... 'Z':
                if (last_was_whitespace) {
                new_identifier:;
                    LEX_CURRENT_TOKEN.type = tok_identifier;
                    LEX_CURRENT_TOKEN.identifier.pos = state.src_head;
                    LEX_CURRENT_TOKEN.identifier.length = 1;

                    LEX_PUSH_TOKEN;
                } else if (LEX_LAST_TOKEN.type == tok_identifier) {
                    LEX_LAST_TOKEN.identifier.length += 1;
                } else {
                    goto new_identifier;
                }
                break;
            case '0' ... '9':
                if (last_was_whitespace) {
                new_literal_int:;
                    LEX_CURRENT_TOKEN.type = tok_literal_int;
                    LEX_CURRENT_TOKEN.literal_int.pos = state.src_head;
                    LEX_CURRENT_TOKEN.literal_int.length = 1;
                    LEX_PUSH_TOKEN;
                } else if (LEX_LAST_TOKEN.type == tok_literal_int) {
                    LEX_LAST_TOKEN.literal_int.length += 1;
                } else if (LEX_LAST_TOKEN.type == tok_identifier) {
                    LEX_LAST_TOKEN.identifier.length += 1;
                } else {
                    goto new_literal_int;
                }
                break;


#define TOKEN(name, c, ...)                          \
    case c: {                                        \
        LEX_CURRENT_TOKEN.type = tok_##name;         \
        LEX_CURRENT_TOKEN.name.pos = state.src_head; \
        LEX_PUSH_TOKEN;                              \
    } break;
                TOKENS_SINGLE_CHAR
#undef TOKEN
        }
        last_was_whitespace = 0;
        ++state.src_head;
    }

#undef LEX_CURRENT_TOKEN
#undef LEX_LAST_TOKEN
#undef LEX_PUSH_TOKEN

    debug_lex_dump_tokens(state);

    return state;
}

struct ast_node;


#define NODES_COMPOUND                            \
    NODE(scope, { struct ast_node* statements; }) \
    NODE(statement, { int dummy; })               \
    /**/

#define NODES      \
    NODES_COMPOUND \
    /**/

#define NODE(name, body) struct ast_##name body;
NODES_COMPOUND
#undef NODE


enum ast_node_type
{
#define NODE(name, ...) ast_##name,
    NODES
#undef NODE
};
struct ast_node
{
    enum ast_node_type type;
    struct ast_node* next;
    union
    {
#define NODE(name, ...) struct ast_##name name;
        NODES
#undef NODE
    };
};


struct parse_state
{
    struct arena node_arena;
    struct ast_node* ast;
    int ast_count;
};


internal void debug_ast_dump_ast(
    struct parse_state* state,
    struct ast_node* current,
    int indent
);

internal void
debug_ast_dump_ast__scope(struct parse_state* state, struct ast_scope s, int indent)
{
    printf("%*cSCOPE\n", indent, ' ');
    for (struct ast_node* current = s.statements; current; current = current->next) {
        debug_ast_dump_ast(state, current, 2 + indent);
    }
    printf("%*cEND_SCOPE\n", indent, ' ');
}
internal void
debug_ast_dump_ast__statement(
    struct parse_state* state,
    struct ast_statement s,
    int indent
)
{
    printf("%*cSTATEMENT\n", indent, ' ');
}
internal void
debug_ast_dump_ast(struct parse_state* state, struct ast_node* current, int indent)
{
    for (; current; current = current->next) {
        switch (current->type) {
            case ast_scope:
                debug_ast_dump_ast__scope(state, current->scope, indent);
                break;
            case ast_statement:
                debug_ast_dump_ast__statement(state, current->statement, indent);
                break;
        }
    }
}


#define zero(p) memset(p, 0, sizeof(*(p)))

internal struct parse_state
parse(struct lex_state* lex)
{
    typedef struct token token_t;
    typedef struct ast_node node_t;

    struct ast_node_with_parent
    {
        struct ast_node* node;
        struct ast_node_with_parent* senior;
    };

    int const MAX_NODES = 1024;

    struct parse_state state = { 0 };
    state.node_arena.capacity = MAX_NODES * sizeof(node_t);
    state.node_arena.data = calloc(state.node_arena.capacity, 1);


    struct arena parent_arena_ = { 0 };
    parent_arena_.capacity = MAX_NODES * sizeof(struct ast_node_with_parent);
    parent_arena_.data = calloc(parent_arena_.capacity, 1);

    struct arena* arena = &state.node_arena;
    struct arena* arena_parent = &parent_arena_;

#define push_parent(NODE)                                             \
    {                                                                 \
        struct ast_node_with_parent* nc = arena_push(                 \
            arena_parent,                                             \
            struct ast_node_with_parent                               \
        );                                                            \
        nc->senior = current;                                         \
        nc->node = NODE;                                              \
        current = nc;                                                 \
        arena_pop(arena_parent, sizeof(struct ast_node_with_parent)); \
    }                                                                 \
    /**/

#define pop_parent (current = current->senior)

    struct ast_node_with_parent* current = 0;
    push_parent(0);

    for (int i = lex->n_tokens - 1; i >= 0; --i) {
        token_t tok = lex->tokens[i];
        switch (tok.type) {
            case tok_brace_l: {
                /* End of the current scope. */
                struct ast_node_with_parent* child_scope = current;
                pop_parent;
                if (!current->node) {
                    /* We were a top-level scope, and we just got closed. */
                    state.ast = child_scope->node;
                } else {
                    switch (current->node->type) {
                        case ast_scope:
                            /* We were a scope-in-scope. */
                            child_scope->node->next = current->node->scope.statements;
                            current->node->scope.statements = child_scope->node;
                            break;
                        case ast_statement:
                            /*TODO:
                                Think what this means.
                                We were a child of a statement, somehow.
                            */
                            break;
                    }
                }
            } break;

            case tok_brace_r: {
                /* New scope. */
                node_t* node_scope = arena_push(arena, node_t);
                zero(node_scope);
                node_scope->type = ast_scope;
                node_scope->next = 0;

                if (current->node) {
                    /* Whatever we are inside, it must be scope. */
                    assert(current->node->type == ast_scope);

                    node_scope->next = current->node->scope.statements;
                }

                /* This is the new parent to all nodes. */
                push_parent(node_scope);

                /* This is also the active node. */
                state.ast = node_scope;
            } break;

            case tok_paren_l:
            case tok_paren_r:

            case tok_identifier:
            case tok_literal_int: break;
            case tok_semicolon: {
                /* Starting a new statement. */
                node_t* node_statement = arena_push(arena, node_t);
                node_statement->type = ast_statement;

                state.ast = node_statement;
            } break;
            case tok_bracket_l:
            case tok_bracket_r:
            case tok_dot:
            case tok_hash:
            case tok_equals:
            case tok_plus:
            case tok_minus:
            case tok_star:
            case tok_slash:
            case tok_colon:
            case tok_question:
            case tok_hat:
            case tok_amp:
            case tok_pipe:
            case tok_at: break;
        }
    }

    puts("----- AST -----");
    debug_ast_dump_ast(&state, state.ast, 0);
    puts("----- END AST -----");


    return state;
}


internal void
compile_to_c(char const* path)
{
    char* source_text = read_file(path);
    if (!source_text) {
        fprintf(stderr, "Cannot open file %s\n", path);
        return;
    }

    puts("------------- SOURCE -------------------");
    puts(source_text);
    puts("----------------------------------------");
    struct lex_state lex_state = lex(path, source_text);
    struct parse_state parse_state = parse(&lex_state);
}
int
main()
{
    compile_to_c("test.bryc");
    return 0;
}