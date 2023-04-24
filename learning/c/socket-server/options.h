#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED

typedef struct server_options
{
    int port;
} server_options;

struct server_options *get_server_options(int argc, char *argv[]);
void print_server_options(struct server_options *options);

#endif