// Standard library includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// "Static" local headers
#include "ast.h"
#include "ast_writer.h"
#include "codegen.h"

// "Dynamic" (i.e. auto-generated) headers
#include "parser.tab.h"

char* construct_dot_filename(char *input_filename);

int main(int argc, char **argv)
{

    extern AST_Root *tree;

    char *input_filename      = NULL;
    char *output_filename     = NULL;
    char *output_dot_filename = NULL;

    int generate_dot_file   = 0;
    int output_filename_set = 0;

    int i;

    // Different targets to compile for
    // 0: Trireme
    // 1: RARS
    // 2: spike
    int target = 0;

    for(i=1;i<argc;i++) 
    {
        if (*argv[i]=='-') 
        {
            switch(*(argv[i]+1)) 
            {
                /* output option */
                case 'o':
                    output_filename = argv[++i];
                    output_filename_set = 1;
                    break;

                case 't':
                    target = 0; break;
                case 'r':
                    target = 1; break;
                case 's':
                    target = 2; break;

                case 'p':
                    generate_dot_file = 1; break;

                default:
                    fprintf(stderr,"%s: unknown argument option\n",argv[0]);
                    exit(1);
            }
        } 
        else 
        {
            if (input_filename != NULL) 
            {
                fprintf(stderr,"%s: only one input file allowed\n",argv[0]);
                fprintf(stderr,"Already have: %s\n", input_filename);
                fprintf(stderr,"Given: %s\n", argv[i]);
                exit(1);
            }

            input_filename = argv[i];
        }
    }

    if (input_filename != NULL) 
    {
        if ((freopen(input_filename, "r",stdin))==NULL) 
        {
            fprintf(stderr,"%s: cannot open input file %s\n",argv[0],input_filename);
            exit(1);
        }
    }

    printf("Target: %d\n", target);

    // Calling yyparse and handling the result-value
    // Based on documentation available at:
    // https://www.gnu.org/software/bison/manual/html_node/Parser-Function.html
    int parsing_result = yyparse();

    switch (parsing_result)
    {
        case 0:
            printf("No errors detected.\n");
            break;
        case 1:
            printf("Errors detected.\n");
            exit(parsing_result);
        case 2:
            printf("Parsing Error: Out of Memory!\n");
            exit(parsing_result);
        default:
            printf("Parsing Error: Unkown Problem!\n");
            exit(parsing_result);
    }

    // Construct a filename for the output .s file if none is given
    if (!output_filename_set)
    {
        // Determine filename length
        // filename + '\0'
        size_t output_filename_len = strlen(input_filename) + 1;

        // Allocate memory for filename
        char *output_filename = (char*) calloc(output_filename_len, sizeof(char));

        // Concatenate literals and args
        // Minus 3 comes from length of ".c" and '\0'
        output_filename = strncat(output_filename, input_filename, output_filename_len-3);
        output_filename = strncat(output_filename, ".s", 2);
    }

    // Construct filename for the .dot file
    if (generate_dot_file)
    {
        // Determine filename length
        // filename + 2 additional characters ('s' vs 'dot') + '\0'
        size_t output_dot_filename_len = strlen(output_filename) + 3;

        // Allocate memory for filename
        output_dot_filename = (char*) calloc(output_dot_filename_len, sizeof(char));

        // Concatenate literals and args
        // Minus 5 comes from length of ".dot" and '\0'
        output_dot_filename = strncat(output_dot_filename, output_filename, output_dot_filename_len-3);
        output_dot_filename = strncat(output_dot_filename, ".dot", 4);
    }
    
    // Write the AST .dot file to disk
    if (output_dot_filename != NULL)
    {
        write_ast_to_dot_file(output_dot_filename, tree);
    }

    // Generate code
    write_ast_to_riscv_file(output_filename, tree, target);

    // Free memory and exit
    if (!output_filename_set)
    {
        free(output_filename);
    }
    exit(parsing_result);
}
