int parse_short_opt(char *arg, cmd_data_t *cmd_data)
{
    if (strcmp(arg, "export-dynamic") == 0) {
        return 1;
    }

    if (strcmp(arg, "module") == 0) {
        return 1;
    }

    if (strcmp(arg, "Zexe") == 0) {
        return 1;
    }

    if (strcmp(arg, "avoid-version") == 0) {
        return 1;
    }

    if (strcmp(arg, "prefer-pic") == 0) {
        return 1;
    }

    if (strcmp(arg, "prefer-non-pic") == 0) {
        return 1;
    }

    if (strcmp(arg, "version-info") == 0 ) {
        return 2;
    }

    return 0;
}