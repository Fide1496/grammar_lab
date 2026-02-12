#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include "lexer.h"
#include "ast.h"
#include "debug.h"

using namespace std;
using Token = int;

// -----------------------------------------------------------------------------
//   <sentence>         -> <noun phrase> <verb phrase> <noun phrase>
//   <noun phrase>      -> <adjective phrase> NOUN
//   <adjective phrase> -> (ARTICLE | POSSESSIVE) ADJECTIVE
//   <verb phrase>      -> VERB | ADVERB <verb phrase>
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// One-token lookahead
// -----------------------------------------------------------------------------
bool   havePeek = false;
Token  peekTok  = 0;
string peekLex;

inline const char* tname(Token t) { return tokName(t); }

Token peek()
{
  if (!havePeek) {
    peekTok = yylex();
    if (peekTok == 0) { peekTok = EOF; peekLex.clear(); }
    else              { peekLex = yytext ? string(yytext) : string(); }
    dbg::line(string("peek: ") + tname(peekTok) + (peekLex.empty() ? "" : " ["+peekLex+"]")
              + " @ line " + to_string(yylineno));
    havePeek = true;
  }
  return peekTok;
}

Token nextTok()
{
  Token t = peek();
  dbg::line(string("consume: ") + tname(t));
  havePeek = false;
  return t;
}

Token expect(Token want, const char* msg)
{
  Token got = nextTok();
  if (got != want) {
    dbg::line(string("expect FAIL: wanted ") + tname(want) + ", got " + tname(got));
    ostringstream oss;
    oss << "Parse error (line " << yylineno << "): expected "
        << tname(want) << " — " << msg << ", got " << tname(got)
        << " [" << (yytext ? yytext : "") << "]";
    throw runtime_error(oss.str());
  }
  return got;
}

// -----------------------------------------------------------------------------
// Forward declarations
// -----------------------------------------------------------------------------
unique_ptr<Sentence> parse_sentence();
unique_ptr<NounPhrase> parse_noun_phrase();
unique_ptr<AdjectivePhrase> parse_adjective_phrase();
unique_ptr<VerbPhrase> parse_verb_phrase();

// -----------------------------------------------------------------------------
// <adjective phrase> -> (ARTICLE | POSSESSIVE) ADJECTIVE
// -----------------------------------------------------------------------------
unique_ptr<AdjectivePhrase> parse_adjective_phrase()
{
    // TODO (Lab 2): implement
    // - read ARTICLE or POSSESSIVE into ap->determiner
    // - read ADJECTIVE into ap->adjective
    // - return the node
    throw runtime_error("TODO: parse_adjective_phrase()");
}


// -----------------------------------------------------------------------------
// <noun phrase> -> <adjective phrase> NOUN
// -----------------------------------------------------------------------------
unique_ptr<NounPhrase> parse_noun_phrase()
{
    // TODO (Lab 2): implement
    // - build noun phrase
    // - parse adjective phrase
    // - expect NOUN
    throw runtime_error("TODO: parse_noun_phrase()");
}


// -----------------------------------------------------------------------------
// <verb phrase> -> VERB | ADVERB <verb phrase>
// Equivalent to: (ADVERB)* VERB
// -----------------------------------------------------------------------------
unique_ptr<VerbPhrase> parse_verb_phrase()
{
    // TODO (Lab 2): implement
    // - consume 0+ ADVERB into vp->adverbs
    // - then expect VERB into vp->verb
    throw runtime_error("TODO: parse_verb_phrase()");
}


// -----------------------------------------------------------------------------
// <sentence> -> <noun phrase> <verb phrase> <noun phrase>
// -----------------------------------------------------------------------------
unique_ptr<Sentence> parse_sentence()
{
    // TODO (Lab 2): implement
    // - subject noun phrase
    // - verb phrase
    // - object noun phrase
    throw runtime_error("TODO: parse_sentence()");
}


// -----------------------------------------------------------------------------
// parse(): entry point called by driver.cpp
// -----------------------------------------------------------------------------
unique_ptr<Sentence> parse()
{
    // Reset lookahead state for a fresh parse
    havePeek = false;
    peekTok = 0;
    peekLex.clear();

    // TODO (Lab 2): parse a sentence and ensure EOF after it
    throw runtime_error("TODO: parse()");
}
