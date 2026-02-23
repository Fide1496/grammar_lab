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
struct AdjectivePhrase : Node
{
    string article;
    string possivie;
    string adj;

    void print_tree(ostream& os, string prefix, bool last)
    {
        ast_line(os, prefix, last, "<adjective phrase>");
        string child_prefix = prefix + (last ? "   ": "|  ");

        if (!article.empty()) ast_line(os, child_prefix, false, "ARTICLE(" + article + ")");
        if (!possivie.empty()) ast_line(os, child_prefix, false, "POSSESSIVE(" + possivie + ")");
        ast_line(os, child_prefix, true, "ADJECTIVE(" + adj + ")");
    }
};

// <noun phrase> -> <adjective phrase> NOUN
struct NounPhrase : Node {
    unique_ptr<AdjectivePhrase> adj;
    string noun;

    void print_tree(ostream& os, string prefix, bool last)
    {
        ast_line(os, prefix, last, "<noun phrase>");
        string child_prefix = prefix + (last ? "   ": "|  ");

        if (adj) adj -> print_tree(os, child_prefix, false);
        ast_line(os, child_prefix, true, "NOUN("+ noun + ")");

    }
};

// <verb phrase>      -> VERB | ADVERB <verb phrase>
struct VerbPhrase : Node
{
    string verb;
    string adverb;
    unique_ptr<VerbPhrase> verb_phase;

    void print_tree(ostream& os, string prefix, bool last)
    {
        ast_line(os, prefix, last, "<verb phrase>");
        string child_prefix = prefix + (last ? "   ": "|  ");

        if (!adverb.empty()) ast_line(os, child_prefix, false, "ADVERB(" + adverb + ")");
        ast_line(os, child_prefix, true, "VERB(" + verb + ")");

        if(verb_phase) verb_phase -> print_tree(os, child_prefix, true);
    }

};

// <sentence> -> <noun phrase> <verb phrase> <noun phrase>
struct Sentence : Node
{

    unique_ptr<NounPhrase> noun1;
    unique_ptr<VerbPhrase> verb;
    unique_ptr<NounPhrase> noun2;

    void print_tree(ostream& os, string prefix, bool last)
    {
        ast_line(os, prefix, last, "<sentence>");
        string child_prefix = prefix + (last ? "   ": "|  ");

        if (noun1) noun1 -> print_tree(os, child_prefix, false);
        if (verb) verb -> print_tree(os, child_prefix, false);
        if (noun2) noun2 -> print_tree(os, child_prefix, true);
    }
};

// <sentence>         -> <noun phrase> <verb phrase> <noun phrase>
// <noun phrase>      -> <adjective phrase> NOUN
// <adjective phrase> -> (ARTICLE | POSSESSIVE) ADJECTIVE
// <verb phrase>      -> VERB | ADVERB <verb phrase>