load("//tools/build_rules:valgrind.bzl", "valgrind_run")

cc_binary(
    name = "string-allocation",
    srcs = ["main.c"],
)

valgrind_run(
    name = "valgrind",
    data = [":string-allocation"],
)
