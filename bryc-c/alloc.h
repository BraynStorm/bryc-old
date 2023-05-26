#pragma once

#include <assert.h>
#include <stddef.h>

#define internal static
#define ARENA internal inline

/* Memory arena. Grown only (for now). */
struct arena
{
    char* data;
    size_t size;
    size_t capacity;
};

/* Clear all thing from this arena. */
ARENA void arena_clear(struct arena* arena);
/* Allocate bytes from the arena. */
ARENA void* arena_push_(struct arena* arena, size_t bytes);

/* Allocate a new object from this arena. */
#define arena_push(arena, type) ((type*)arena_push_(arena, sizeof(type)))
/* Allocate an array of objects from this arena. */
#define arena_push_array(arena, type, count) \
    ((type*)arena_push_(arena, sizeof(type) * count))


ARENA void
arena_clear(struct arena* arena)
{
    arena->size = 0;
}

/* DANGEROUS! */
ARENA void
arena_pop(struct arena* arena, size_t bytes)
{
    assert(bytes <= arena->size);

    arena->size -= bytes;
}
ARENA void*
arena_push_(struct arena* arena, size_t bytes)
{
    assert(arena->size + bytes <= arena->capacity);

    char* result = arena->data + arena->size;
    arena->size += bytes;
    return result;
}
