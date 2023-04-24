load("//tools/build_rules:valgrind.bzl", "valgrind_run")

cc_binary(
    name = "two-d-array",
    srcs = ["main.c"],
)

valgrind_run(
    name = "valgrind",
    data = [":two-d-array"],
)
