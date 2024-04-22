#include "build_c/build.h"

/* ========================================================================= */

struct CompileData target_exe_files[] = {
    DIR("build/"),

    SP(CT_C, "main.c"),
};

enum CompileResult target_exe() {
    START;
    DO(compile(LI(target_exe_files)));
    DO(link_exe(LI(target_exe_files), "build/uxxd.exe"));
    END;
}

/* ========================================================================= */

struct Target targets[] = {
	{ .name = "uxxd.exe", .run = target_exe },
};

#define TARGETS_LEN (sizeof(targets) / sizeof(targets[0]))

int main(int argc, char **argv) {
    return build_main(argc, argv, targets, TARGETS_LEN);
}
