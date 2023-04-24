def _valgrind_script_gen(ctx, script):
    dummy_output = ctx.actions.declare_file(ctx.label.name + ".dummy")

    executable_path = ctx.attr.data[0].files_to_run.executable.short_path
    ctx.actions.write(
        output = script,
        is_executable = True,
        content = """#!/bin/bash\nvalgrind --leak-check=full --error-exitcode=1 ./{0}""".format(executable_path),
    )

    ctx.actions.run_shell(
        outputs = [dummy_output],
        inputs = [script],
        command = "chmod +x {}".format(script.path),
    )

def _valgrind_test_impl(ctx):
    test_script = ctx.actions.declare_file(ctx.label.name + ".sh")

    _valgrind_script_gen(ctx, test_script)

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

def _valgrind_run_impl(ctx):
    run_script = ctx.actions.declare_file(ctx.label.name + ".sh")

    _valgrind_script_gen(ctx, run_script)

    runfiles = ctx.runfiles(files = ctx.files.data + [run_script])
    return [
        DefaultInfo(
            executable = run_script,
            runfiles = runfiles,
        ),
    ]

valgrind_run = rule(
    implementation = _valgrind_run_impl,
    attrs = {
        "data": attr.label_list(allow_files = True),
    },
    executable = True,
)
