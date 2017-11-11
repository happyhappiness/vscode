int parse_long_opt(char *arg, command_t *cmd_data)
{
    char *equal_pos = strchr(arg, '=');
    char var[50];
    char value[500];

    if (equal_pos) {
        strncpy(var, arg, equal_pos - arg);
        var[equal_pos - arg] = 0;
        strcpy(value, equal_pos + 1);
    } else {
        strcpy(var, arg);
    }

    if (strcmp(var, "silent") == 0) {
        cmd_data->options.silent = 1;
    } else if (strcmp(var, "mode") == 0) {
        if (strcmp(value, "compile") == 0) {
            cmd_data->mode = mCompile;
            cmd_data->output = otObject;
        }

        if (strcmp(value, "link") == 0) {
            cmd_data->mode = mLink;
            cmd_data->output = otLibrary;
        }

        if (strcmp(value, "install") == 0) {
            cmd_data->mode = mInstall;
        }
    } else if (strcmp(var, "shared") == 0) {
        if (cmd_data->mode == mLink) {
            cmd_data->output = otDynamicLibraryOnly;
        }
        cmd_data->options.shared = 1;
    } else if (strcmp(var, "export-all") == 0) {
        cmd_data->options.export_all = 1;
    } else if (strcmp(var, "dry-run") == 0) {
        printf("Dry-run mode on!\n");
        cmd_data->options.dry_run = 1;
    } else if (strcmp(var, "version") == 0) {
        printf("Version " VERSION "\n");
    } else if (strcmp(var, "help") == 0) {
        printf("Sorry.  No help available.\n");
    } else if (strcmp(var, "config") == 0) {
        print_config();
    } else if (strcmp(var, "tag") == 0) {
        if (strcmp(value, "CC") == 0) {
            /* Do nothing. */
        }
        if (strcmp(value, "CXX") == 0) {
            /* Do nothing. */
        }
    } else {
        return 0;
    }

    return 1;
}