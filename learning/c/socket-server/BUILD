load("//tools/build_rules:valgrind.bzl", "valgrind_run")

cc_library(
    name = "options",
    srcs = ["options.c"],
    hdrs = ["options.h"],
)

cc_binary(
    name = "socket-server",
    srcs = ["main.c"],
    deps = [":options"],
)

valgrind_run(
    name = "valgrind",
    data = [":socket-server"],
)
