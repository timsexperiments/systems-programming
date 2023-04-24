#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <ctype.h>

static struct option long_options[] = {
    {"input", required_argument, 0, 'i'},
    {"output", required_argument, 0, 'o'},
    {"verbose", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}};

int main(int argc, char *argv[])
{
    int c;
    int verboseflag = 0, helpflag = 0;
    char *input = NULL, *output = NULL;

    while ((c = getopt_long(argc, argv, "i:o:vh", long_options, NULL)) != -1)
    {
        switch (c)
        {
        case 'i':
            input = optarg;
            break;
        case 'o':
            output = optarg;
            break;
        case 'h':
            printf("Usage: %s [OPTIONS]\n", argv[0]);
            printf("Options:\n");
            printf("\t-i, --input=FILE_PATH\t\tSpecify input file\n");
            printf("\t-o, --output=FILE_PATH\t\tSpecify output file\n");
            printf("\t-v, --verbose\t\t\tEnable verbose mode\n");
            printf("\t-h, --help\t\t\tShow this help message\n");
            return 0;
        case 'v':
            verboseflag = 1;
            break;
        case '?':
            if (optopt == 'i' || optopt == 'o')
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint(optopt))
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
            return 1;
        default:
            abort();
        }
    }

    printf("input = %s, output = %s, verbose = %d\n", input, output, verboseflag);

    return 0;
}