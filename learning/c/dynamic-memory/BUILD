load("//tools/build_rules:valgrind.bzl", "valgrind_test")

cc_binary(
    name = "dynamic-memory",
    srcs = ["main.c"],
)

valgrind_test(
    name = "valgrind",
    data = [":dynamic-memory"],
)
