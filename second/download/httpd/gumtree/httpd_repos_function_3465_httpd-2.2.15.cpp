bool parse_long_opt(char *arg, cmd_data_t *cmd_data)
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
        silent = true;
    } else if (strcmp(var, "mode") == 0) {
        if (strcmp(value, "compile") == 0) {
            cmd_data->mode = mCompile;
            cmd_data->output_type = otObject;
        }

        if (strcmp(value, "link") == 0) {
            cmd_data->mode = mLink;
        }

        if (strcmp(value, "install") == 0) {
            cmd_data->mode = mInstall;
        }
    } else if (strcmp(var, "shared") == 0) {
        shared = true;
    } else if (strcmp(var, "export-all") == 0) {
        export_all = true;
    } else {
        return false;
    }

    return true;
}