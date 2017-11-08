int parse_short_opt(char *arg, command_t *cmd_data)
{
    if (strcmp(arg, "export-dynamic") == 0) {
        cmd_data->options.export_dynamic = 1;
        return 1;
    }

    if (strcmp(arg, "module") == 0) {
        cmd_data->output = otModule;
        return 1;
    }

    if (strcmp(arg, "shared") == 0) {
        if (cmd_data->mode == mLink) {
            cmd_data->output = otDynamicLibraryOnly;
        }
        cmd_data->options.shared = share_SHARED;
        return 1;
    }

    if (strcmp(arg, "Zexe") == 0) {
        return 1;
    }

    if (strcmp(arg, "avoid-version") == 0) {
        return 1;
    }

    if (strcmp(arg, "prefer-pic") == 0) {
        cmd_data->options.pic_mode = pic_PREFER;
        return 1;
    }

    if (strcmp(arg, "prefer-non-pic") == 0) {
        cmd_data->options.pic_mode = pic_AVOID;
        return 1;
    }

    if (strcmp(arg, "static") == 0) {
        cmd_data->options.shared = share_STATIC;
        return 1;
    }

    if (cmd_data->mode == mLink) {
        if (strcmp(arg, "no-install") == 0) {
            cmd_data->options.no_install = 1;
            return 1;
        }
        if (arg[0] == 'L' || arg[0] == 'l') {
            /* Hack... */
            arg--;
            push_count_chars(cmd_data->shared_opts.dependencies, arg);
            return 1;
        } else if (arg[0] == 'R' && arg[1]) {
            /* -Rdir Add dir to runtime library search path. */
            add_runtimedirlib(&arg[1], cmd_data);
            return 1;
        }
    }
    return 0;
}