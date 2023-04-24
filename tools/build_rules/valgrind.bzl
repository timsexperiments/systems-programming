def _valgrind_test_impl(ctx):
    test_script = ctx.actions.declare_file(ctx.label.name + ".sh")
    dummy_output = ctx.actions.declare_file(ctx.label.name + ".dummy")

    executable_path = ctx.attr.data[0].files_to_run.executable.short_path
    ctx.actions.write(
        output = test_script,
        content = """#!/bin/bash\necho "$PWD"\nvalgrind --leak-check=full --error-exitcode=1 ./{0}""".format(executable_path),
    )

    ctx.actions.run_shell(
        outputs = [dummy_output],
        inputs = ctx.files.data + [test_script],
        command = "chmod +x {}".format(test_script.path),
    )

    runfiles = ctx.runfiles(files = ctx.files.data + [test_script])
    return [
        DefaultInfo(
            executable = test_script,
            runfiles = runfiles,
        ),
    ]

valgrind_test = rule(
    implementation = _valgrind_test_impl,
    attrs = {
        "data": attr.label_list(allow_files = True),
    },
    test = True,
)
