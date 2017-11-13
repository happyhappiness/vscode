void parse_args(int argc, char *argv[], command_t *cmd_data)
{
    int a;
    char *arg;
    int argused;

    for (a = 1; a < argc; a++) {
        arg = argv[a];
        argused = 1;

        if (arg[0] == '-') {
            if (arg[1] == '-') {
                argused = parse_long_opt(arg + 2, cmd_data);
            }
            else {
                argused = parse_short_opt(arg + 1, cmd_data);
            }

            /* We haven't done anything with it yet, try some of the
             * more complicated short opts... */
            if (argused == 0 && a + 1 < argc) {
                if (arg[1] == 'o' && !arg[2]) {
                    arg = argv[++a];
                    argused = parse_output_file_name(arg, cmd_data);
                } else if (strcmp(arg+1, "MT") == 0) {
                    if (!cmd_data->options.silent) {
                        printf("Adding: %s", arg);
                    }
                    push_count_chars(cmd_data->arglist, arg);
                    arg = argv[++a];
                    if (!cmd_data->options.silent) {
                        printf(" %s\n", arg);
                    }
                    push_count_chars(cmd_data->arglist, arg);
                    argused = 1;
                } else if (strcmp(arg+1, "rpath") == 0) {
                    /* Aha, we should try to link both! */
                    cmd_data->install_path = argv[++a];
                    argused = 1;
                } else if (strcmp(arg+1, "version-info") == 0) {
                    /* Store for later deciphering */
                    cmd_data->version_info = argv[++a];
                    argused = 1;
                } else if (strcmp(arg+1, "export-symbols-regex") == 0) {
                    /* Skip the argument. */
                    ++a;
                    argused = 1;
                } else if (arg[1] == 'R' && !arg[2]) {
                    /* -R dir Add dir to runtime library search path. */
                    add_runtimedirlib(argv[++a], cmd_data);
                    argused = 1;
                }
            }
        } else {
            argused = parse_input_file_name(arg, cmd_data);
        }

        if (!argused) {
            if (!cmd_data->options.silent) {
                printf("Adding: %s\n", arg);
            }
            push_count_chars(cmd_data->arglist, arg);
        }
    }

}