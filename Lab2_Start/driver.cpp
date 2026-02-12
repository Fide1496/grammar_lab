#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "lexer.h"
#include "ast.h"
#include "debug.h"

using namespace std;

// parser.cpp provides this.
unique_ptr<Sentence> parse();

static void usage(const char* prog)
{
    cerr << "usage: " << prog << " [-d] <inputfile>\n";
    cerr << "  -d   enable debug tracing (debug.h)\n";
}

int main(int argc, char** argv)
{
    try {
        bool debug_on = false;
        string path;

        for (int i = 1; i < argc; ++i) {
            string arg = argv[i];
            if (arg == "-d") {
                debug_on = true;
            } else if (!arg.empty() && arg[0] == '-') {
                usage(argv[0]);
                return 1;
            } else {
                path = arg;
            }
        }

        if (path.empty()) {
            usage(argv[0]);
            return 1;
        }

        dbg::set(debug_on);


        yyin = fopen(path.c_str(), "r");
        if (!yyin) {
            cerr << "could not open: " << path << "\n";
            return 1;
        }

        auto root = parse();

        // Print the AST tree
        root->print_tree(cout, "", true);

        fclose(yyin);
        return 0;
    }
    catch (exception& e) {
        cerr << e.what() << "\n";
        return 1;
    }
}
