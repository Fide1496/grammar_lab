#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

// -----------------------------------------------------------------------------
// Forward declarations
// -----------------------------------------------------------------------------
struct Node;
struct AdjectivePhrase;
struct NounPhrase;
struct VerbPhrase;
struct Sentence;

// -----------------------------------------------------------------------------
// Grammar 
// -----------------------------------------------------------------------------
// <sentence>         -> <noun phrase> <verb phrase> <noun phrase>
// <noun phrase>      -> <adjective phrase> NOUN
// <adjective phrase> -> (ARTICLE | POSSESSIVE) ADJECTIVE
// <verb phrase>      -> VERB | ADVERB <verb phrase>
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Pretty printer (tree-style)
// -----------------------------------------------------------------------------
inline void ast_line(ostream& os, string prefix, bool last, string label)
{
    os << prefix << (last ? "+-- " : "|-- ") << label << "\n";
}

// -----------------------------------------------------------------------------
// Base AST node
// -----------------------------------------------------------------------------
struct Node {
    virtual ~Node() = default;
    virtual void print_tree(ostream& os, string prefix, bool last) = 0;
};
// -----------------------------------------------------------------------------
// Base AST node
// -----------------------------------------------------------------------------
// struct Node {
//     virtual ~Node() = default;
//     virtual void print_tree(ostream& os, string prefix, bool last) = 0;
// };

// -----------------------------------------------------------------------------
// Student AST design area
// -----------------------------------------------------------------------------
// TODO (Lab 2): Design your AST structs.
//
// Requirements:
//  1) There must be ONE AST node per nonterminal in the grammar above.
//  2) Store lexeme strings from yytext (e.g., "the", "my", "big", "dog", ...).
//  3) Every node must implement print_tree(...) using ast_line(...).
//  4) Keep the file in "top-down" order if you want (Sentence first), but if you
//     do that you may need out-of-line print_tree definitions to avoid
//     incomplete-type errors.
//
// Suggested (not required) node names:
//   Sentence, NounPhrase, VerbPhrase, AdjectivePhrase
//
// Tip: VerbPhrase can be represented as (ADVERB)* VERB in your AST.
//

// --- Put your structs below this line ----------------------------------------

// <adjective phrase> -> (ARTICLE | POSSESSIVE) ADJECTIVE
// <sentence> -> <noun phrase> <verb phrase> <noun phrase>


struct AdjectivePhrase : Node
{
    string determiner;
    string adjective;

    void print_tree(ostream& os, string prefix, bool last)
    {
        ast_line(os, prefix, last, "<adjective phrase>");
        string child_prefix = prefix + (last ? "    ": "|   ");

        ast_line(os, child_prefix, false, "DETERMINER(" + determiner + ")");
        ast_line(os, child_prefix, true, "ADJECTIVE(" + adjective + ")");
    }
};

// <noun phrase> -> <adjective phrase> NOUN
struct NounPhrase : Node {
    unique_ptr<AdjectivePhrase> ap;
    string noun;

    void print_tree(ostream& os, string prefix, bool last)
    {
        ast_line(os, prefix, last, "<noun phrase>");
        string child_prefix = prefix + (last ? "    ": "|   ");

        if (ap) ap -> print_tree(os, child_prefix, false);
        ast_line(os, child_prefix, true, "NOUN(" + noun + ")");

    }
};



// <verb phrase>      -> VERB | ADVERB <verb phrase>
struct VerbPhrase : Node
{
    string verb;
    vector<string> adverbs;

    void print_tree(ostream& os, string prefix, bool last)
    {
        ast_line(os, prefix, last, "<verb phrase>");
        string child_prefix = prefix + (last ? "    ": "|   ");

        for (const auto& adverb : adverbs) {
            ast_line(os, child_prefix, false, "ADVERB(" + adverb + ")");
        }
        ast_line(os, child_prefix, true, "VERB(" + verb + ")");
    }

};

struct Sentence : Node
{
    unique_ptr<NounPhrase> subject_noun;
    unique_ptr<VerbPhrase> verb;
    unique_ptr<NounPhrase> object_noun;

    void print_tree(ostream& os, string prefix, bool last)
    {
        ast_line(os, prefix, last, "<sentence>");
        string child_prefix = prefix + (last ? "    ": "|   ");

        if (subject_noun) subject_noun -> print_tree(os, child_prefix, false);
        if (verb) verb -> print_tree(os, child_prefix, false);
        if (object_noun) object_noun -> print_tree(os, child_prefix, true);
    }
};
// <sentence>         -> <noun phrase> <verb phrase> <noun phrase>
// <noun phrase>      -> <adjective phrase> NOUN
// <adjective phrase> -> (ARTICLE | POSSESSIVE) ADJECTIVE
// <verb phrase>      -> VERB | ADVERB <verb phrase>