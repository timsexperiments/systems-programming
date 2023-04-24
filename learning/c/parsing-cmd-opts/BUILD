load("//tools/build_rules:valgrind.bzl", "valgrind_test")

cc_binary(
    name = "parsing-cmd-opts",
    srcs = ["main.c"],
)

valgrind_test(
    name = "valgrind",
    data = [":parsing-cmd-opts"],
)
