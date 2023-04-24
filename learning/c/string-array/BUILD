load("//tools/build_rules:valgrind.bzl", "valgrind_run")

cc_binary(
    name = "string-array",
    srcs = ["main.c"],
)

valgrind_run(
    name = "valgrind",
    data = [":string-array"],
)
