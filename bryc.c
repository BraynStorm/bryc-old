#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define internal static
#define global static

// clang-format off
global char const CONTENT_CLANG_FORMAT[] =
"# Created by Bozhidar Stoyanov "
"(braynstorm).\n"
"---\n"
"Language: Cpp\n"
"AccessModifierOffset: -4\n"
"AlignAfterOpenBracket: BlockIndent\n"
"AlignArrayOfStructures: Right\n"
"AlignConsecutiveMacros: None\n"
"AlignConsecutiveAssignments: None\n"
"AlignConsecutiveBitFields: None\n"
"AlignConsecutiveDeclarations: None\n"
"AlignEscapedNewlines: Left\n"
"AlignOperands: Align\n"
"AlignTrailingComments: true\n"
"AllowAllArgumentsOnNextLine: false\n"
"AllowAllParametersOfDeclarationOnNextLine: "
"false\n"
"AllowShortEnumsOnASingleLine: true\n"
"AllowShortBlocksOnASingleLine: Never\n"
"AllowShortCaseLabelsOnASingleLine: true\n"
"AllowShortFunctionsOnASingleLine: Inline\n"
"AllowShortLambdasOnASingleLine: All\n"
"AllowShortIfStatementsOnASingleLine: "
"Never\n"
"AllowShortLoopsOnASingleLine: false\n"
"AlwaysBreakAfterDefinitionReturnType: All\n"
"AlwaysBreakAfterReturnType: "
"AllDefinitions\n"
"AlwaysBreakBeforeMultilineStrings: false\n"
"AlwaysBreakTemplateDeclarations: Yes\n"
"AttributeMacros:\n"
"  - __capability\n"
"BinPackArguments: false\n"
"BinPackParameters: false\n"
"BraceWrapping:\n"
"  AfterCaseLabel: false\n"
"  AfterClass: true\n"
"  AfterControlStatement: Never\n"
"  AfterEnum: true\n"
"  AfterFunction: true\n"
"  AfterNamespace: false\n"
"  AfterObjCDeclaration: false\n"
"  AfterStruct: true\n"
"  AfterUnion: true\n"
"  AfterExternBlock: false\n"
"  BeforeCatch: false\n"
"  BeforeElse: false\n"
"  BeforeLambdaBody: false\n"
"  BeforeWhile: false\n"
"  IndentBraces: false\n"
"  SplitEmptyFunction: true\n"
"  SplitEmptyRecord: false\n"
"  SplitEmptyNamespace: true\n"
"BreakBeforeBinaryOperators: true\n"
"BreakBeforeConceptDeclarations: true\n"
"BreakBeforeBraces: Custom\n"
"BreakBeforeInheritanceComma: false\n"
"BreakInheritanceList: BeforeComma\n"
"BreakBeforeTernaryOperators: true\n"
"BreakConstructorInitializersBeforeComma: "
"false\n"
"BreakConstructorInitializers: BeforeComma\n"
"BreakAfterJavaFieldAnnotations: false\n"
"BreakStringLiterals: true\n"
"ColumnLimit: 88\n"
"CommentPragmas: \"^ IWYU pragma:\"\n"
"QualifierAlignment: Right\n"
"CompactNamespaces: true\n"
"ConstructorInitializerIndentWidth: 2\n"
"ContinuationIndentWidth: 4\n"
"Cpp11BracedListStyle: false\n"
"DeriveLineEnding: true\n"
"DerivePointerAlignment: false\n"
"DisableFormat: false\n"
"EmptyLineAfterAccessModifier: Never\n"
"EmptyLineBeforeAccessModifier: "
"LogicalBlock\n"
"ExperimentalAutoDetectBinPacking: false\n"
"PackConstructorInitializers: Never\n"
"BasedOnStyle: \"\"\n"
"FixNamespaceComments: true\n"
"ForEachMacros:\n"
"  - foreach\n"
"  - Q_FOREACH\n"
"  - BOOST_FOREACH\n"
"IfMacros:\n"
"  - KJ_IF_MAYBE\n"
"IncludeBlocks: Preserve\n"
"IncludeCategories:\n"
"  - Regex: "
"'^\"(llvm|llvm-c|clang|clang-c)/'\n"
"    Priority: 2\n"
"    SortPriority: 0\n"
"    CaseSensitive: false\n"
"  - Regex: "
"'^(<|\"(gtest|gmock|isl|json)/)'\n"
"    Priority: 3\n"
"    SortPriority: 0\n"
"    CaseSensitive: false\n"
"  - Regex: \".*\"\n"
"    Priority: 1\n"
"    SortPriority: 0\n"
"    CaseSensitive: false\n"
"IncludeIsMainRegex: \"(Test)?$\"\n"
"IncludeIsMainSourceRegex: \"\"\n"
"IndentAccessModifiers: false\n"
"IndentCaseLabels: true\n"
"IndentCaseBlocks: false\n"
"IndentGotoLabels: true\n"
"IndentPPDirectives: None\n"
"IndentExternBlock: NoIndent\n"
"IndentRequires: false\n"
"IndentWidth: 4\n"
"IndentWrappedFunctionNames: false\n"
"InsertTrailingCommas: Wrapped\n"
"JavaScriptQuotes: Leave\n"
"JavaScriptWrapImports: true\n"
"KeepEmptyLinesAtTheStartOfBlocks: true\n"
"LambdaBodyIndentation: Signature\n"
"MacroBlockBegin: \"\"\n"
"MacroBlockEnd: \"\"\n"
"MaxEmptyLinesToKeep: 2\n"
"NamespaceIndentation: All\n"
"ObjCBinPackProtocolList: Auto\n"
"ObjCBlockIndentWidth: 2\n"
"ObjCBreakBeforeNestedBlockParam: true\n"
"ObjCSpaceAfterProperty: true\n"
"ObjCSpaceBeforeProtocolList: false\n"
"PenaltyBreakAssignment: 20000\n"
"PenaltyBreakBeforeFirstCallParameter: 0\n"
"PenaltyBreakComment: 300\n"
"PenaltyBreakFirstLessLess: 120\n"
"PenaltyBreakOpenParenthesis: 0\n"
"PenaltyBreakString: 1000\n"
"PenaltyBreakTemplateDeclaration: 10\n"
"PenaltyExcessCharacter: 1000000\n"
"PenaltyReturnTypeOnItsOwnLine: 9999999\n"
"PenaltyIndentedWhitespace: 0\n"
"PointerAlignment: Left\n"
"PPIndentWidth: -1\n"
"ReferenceAlignment: Pointer\n"
"ReflowComments: true\n"
"RemoveBracesLLVM: false\n"
"SeparateDefinitionBlocks: Leave\n"
"ShortNamespaceLines: 1\n"
"SortIncludes: Never\n"
"SortJavaStaticImport: Before\n"
"SortUsingDeclarations: false\n"
"SpaceAfterCStyleCast: false\n"
"SpaceAfterLogicalNot: false\n"
"SpaceAfterTemplateKeyword: false\n"
"SpaceBeforeAssignmentOperators: true\n"
"SpaceBeforeCaseColon: false\n"
"SpaceBeforeCpp11BracedList: false\n"
"SpaceBeforeCtorInitializerColon: true\n"
"SpaceBeforeInheritanceColon: true\n"
"SpaceBeforeParens: ControlStatements\n"
"SpaceBeforeParensOptions:\n"
"  AfterControlStatements: true\n"
"  AfterForeachMacros: true\n"
"  AfterFunctionDefinitionName: false\n"
"  AfterFunctionDeclarationName: false\n"
"  AfterIfMacros: true\n"
"  AfterOverloadedOperator: false\n"
"  BeforeNonEmptyParentheses: false\n"
"SpaceAroundPointerQualifiers: Default\n"
"SpaceBeforeRangeBasedForLoopColon: true\n"
"SpaceInEmptyBlock: false\n"
"SpaceInEmptyParentheses: false\n"
"SpacesBeforeTrailingComments: 1\n"
"SpacesInAngles: Never\n"
"SpacesInConditionalStatement: false\n"
"SpacesInContainerLiterals: false\n"
"SpacesInCStyleCastParentheses: false\n"
"SpacesInLineCommentPrefix:\n"
"  Minimum: 1\n"
"  Maximum: -1\n"
"SpacesInParentheses: false\n"
"SpacesInSquareBrackets: false\n"
"SpaceBeforeSquareBrackets: false\n"
"BitFieldColonSpacing: Both\n"
"Standard: c++17\n"
"StatementAttributeLikeMacros:\n"
"  - Q_EMIT\n"
"StatementMacros:\n"
"  - Q_UNUSED\n"
"  - QT_REQUIRE_VERSION\n"
"TabWidth: 4\n"
"UseCRLF: false\n"
"UseTab: Never\n"
"WhitespaceSensitiveMacros:\n"
"  - STRINGIZE\n"
"  - PP_STRINGIZE\n"
"  - BOOST_PP_STRINGIZE\n"
"  - NS_SWIFT_NAME\n"
"  - CF_SWIFT_NAME\n"
"---\n\n";
// clang-format on

struct version
{
    int major;
    int minor;
    int patch;

#define SPRINTF_VERSION (v)(v).major, (v).minor, (v).patch
};


struct project
{
    char const* name;
    char const* cmake_min_version;
    struct version version;
};

typedef int(generator_file_contents)(FILE*, struct project const*);

internal int
gen_clang_format(FILE* file, struct project const* pr)
{
    fwrite(CONTENT_CLANG_FORMAT, 1, sizeof(CONTENT_CLANG_FORMAT) - 1, file);
    return 0;
}

internal int
gen_cmake_lists(FILE* file, struct project const* pr)
{
    fprintf(
        file,
        "cmake_minimum_required(VERSION %s)\n"
        "include(version.cmake)\n"
        "project(%s)\n",
        pr->cmake_min_version,
        pr->name
    );
    return 0;
}
internal int
gen_cmake_version(FILE* file, struct project const* pr)
{
    fprintf(
        file,
        "set(%s_VERSION_MAJOR %d)\n"
        "set(%s_VERSION_MINOR %d)\n"
        "set(%s_VERSION_PATCH %d)\n",
        pr->name,
        pr->version.major,
        pr->name,
        pr->version.minor,
        pr->name,
        pr->version.patch
    );
    return 0;
}

internal int
gen_gitignore(FILE* file, struct project const* pr)
{
    fprintf(
        file,
        ".vscode\n"
        ".cache\n"
        "compile_commands.json\n"
        "build\n"
        "run\n"
    );
    return 0;
}

internal int
create_file(
    char const* path,
    struct project const* pr,
    generator_file_contents* file_contents
)
{
    FILE* file = 0;

    if (!fopen_s(&file, path, "w")) {
        int r = file_contents(file, pr);
        fclose(file);
        return r;
    }
    return -1;
}


int
main(int argc, char** argv)
{
    struct project pr = { 0 };
    if (argc > 1) {
        char const* command = argv[1];
        if (strcmp(command, "--exists") == 0) {
            return 0;
        }
        if (strcmp(command, "--init") == 0) {
#define GET_ARG(i, name, default) pr.name = argc > i ? argv[i] : default
            GET_ARG(2, name, "example");
            GET_ARG(3, cmake_min_version, "3.18");
#undef GET_ARG

            create_file("version.cmake", &pr, gen_cmake_version);
            create_file("CMakeLists.txt", &pr, gen_cmake_lists);
            create_file(".clang-format", &pr, gen_clang_format);
            create_file(".gitignore", &pr, gen_gitignore);
            return 0;
        }
    }
    return 0;
}