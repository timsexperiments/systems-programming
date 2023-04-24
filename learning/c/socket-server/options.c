#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include "options.h"

static struct option long_server_options[] = {
    {"port", required_argument, 0, 'p'},
    {"help", no_argument, 0, 'h'},
    NULL,
};

int is_number(char *str_number)
{
    for (int i = 0; str_number[i] != '\0'; i++)
    {
        if (!isdigit(str_number[i]))
        {
            return 0;
        }
    }
    return 1;
}

void print_server_options(struct server_options *options)
{
    printf("server_options[%p]{ port = %d }\n", options, options->port);
}

struct server_options *get_server_options(int argc, char *argv[])
{
    struct server_options *options = malloc(sizeof(struct server_options));
    options->port = 3000;
    int c;
    fprintf(stdout, "HERE %d\n", __LINE__);
    while ((c = getopt_long(argc, argv, "p:h", long_server_options, NULL)) != -1)
    {
        fprintf(stdout, "HERE %d\n", __LINE__);
        fprintf(stdout, "%c, %s, %c\n\n\n\n\n\n\n\n", c, optarg, optopt);
        switch (c)
        {
        case 'p':
            fprintf(stdout, "%s\n", optarg);
            if (is_number(optarg))
                sprintf(optarg, "%d", options->port);
            else
                printf("%s is not a valid port\n", optarg);
            break;
        case 'h':
            fprintf(stdout, "Usage: %s [OPTIONS]\n", argv[0]);
            fprintf(stdout, "Options:\n");
            fprintf(stdout, "\t-i, --input=FILE_PATH\t\tSpecify input file\n");
            exit(0);
            break;
        default: /* '?' */
            fprintf(stderr, "Usage: %s [-p port]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    printf("HERE %d\n", __LINE__);
    return options;
}
