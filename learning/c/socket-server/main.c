#include <stdlib.h>
#include <sys/socket.h>
#include "options.h"

int main(int argc, char *argv[])
{
    struct server_options *options = get_server_options(argc, argv);
    print_server_options(options);
    free(options);
    options = NULL;
    return 0;
}