#include <stdio.h>
#include <string.h>

char *basename(char *path) {
    char *res = strrchr(path, '/');
    res = (res == NULL) ? path : res + 1;

    char *res2 = strrchr(res, '\\');
    res2 = (res2 == NULL) ? res : res2 + 1;

    return res2;
}

void cescape(char *str) {
    size_t i = strlen(str);
    while (i --> 0) {
        char c = str[i];
        switch (c) {
            case '-':
                c = '_';
            break;

            case '.':
                c = '_';
            break;

            default:
                break;
        }
        str[i] = c;
    }
}

int main(const int argc, char **argv) {
    if (argc != 5)
        goto invalid_usage;

    if (strcmp(argv[1], "-i") != 0)
        goto invalid_usage;

    if (strcmp(argv[3], "-o") != 0)
        goto invalid_usage;

    char *path = argv[2];
    FILE *in;
    if (strcmp(argv[2], "-") == 0) {
        in = stdin;
    } else {
        in = fopen(path, "rb");
        if (in == NULL) {
            fputs("Input file could not be opened!", stderr);
            return 1;
        }
    }

    FILE *out;
    if (strcmp(argv[4], "-") == 0) {
        out = stdout;
    } else {
        out = fopen(argv[4], "w");
        if (out == NULL) {
            fputs("Output file could not be opened!", stderr);
            return 1;
        }
    }

    // destroys path
    char *symname = basename(path);
    cescape(symname);

    fprintf(out, "unsigned char %s[] = {\n  ", symname);

    size_t total = 0;
    do {
        const int c = fgetc(in);
        if (feof(in))
            break;
        if (total > 0)
            fputs(", ", out);
        fprintf(out, "0x%02X", c);
        total ++;
    } while (1);

    if (ferror(in) != 0)
        fputs("Error occured during reading input file!\n", stderr);

    fclose(in);

    fprintf(out, "\n};\n\nunsigned int %s_len = %zu;", symname, total);

    fclose(out);

    return 0;

invalid_usage:
    fputs("xxd -i [in] -o [out]", stderr);
    return 1;
}