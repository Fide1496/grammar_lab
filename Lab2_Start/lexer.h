#ifndef LEXER_H
#define LEXER_H

// ============================================================================
// lexer.h - Token codes shared by the lexer (rules.l) and the parser
// ----------------------------------------------------------------------------
// Author: Derek Willis
//
// Naming conventions:
//   - Token type: Token
//   - Token values: ALL_CAPS (ARTICLE, NOUN, VERB, ...)
//   - End-of-file token code: TOK_EOF (must be 0)
//   - Named tokens start at 256 to avoid collisions with raw character codes (0..255)
//
// Notes:
//   - Flex returns 0 at end-of-file.
//   - Parser code may treat 0 as TOK_EOF.
// ============================================================================

#include <cstdio>   // for std::FILE
using std::FILE;
typedef int Token;
#define TOK_EOF     0

#define ARTICLE     256
#define POSSESSIVE  257
#define ADJECTIVE   258
#define NOUN        259
#define VERB        260
#define ADVERB      261

#define UNKNOWN     299

// Human-readable token names (for debug output).
inline const char* tokName(Token t)
{
    switch (t) {
        case TOK_EOF:     return "TOK_EOF";
        case ARTICLE:     return "ARTICLE";
        case POSSESSIVE:  return "POSSESSIVE";
        case ADJECTIVE:   return "ADJECTIVE";
        case NOUN:        return "NOUN";
        case VERB:        return "VERB";
        case ADVERB:      return "ADVERB";
        case UNKNOWN:     return "UNKNOWN";
        default:          return "<char token>"; // for raw character returns
    }
}

// Scanner interface (provided by Flex in lex.yy.c). Compiled as C++ here.
int   yylex();       // returns one of the Token values above (or a char code)
extern char* yytext; // matched lexeme text
extern int   yylineno;
extern FILE* yyin;   // input stream for the lexer (set in driver/parser)

#endif // LEXER_H
