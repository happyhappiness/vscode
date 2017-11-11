void post_parse_fixup(cmd_data_t *cmd_data)
{
    int a;
    char *arg;
    char *ext;

    if (cmd_data->output_type == otStaticLibrary && cmd_data->mode == mLink) {
        /* We do a real hatchet job on the args when making a static library
         * removing all compiler switches & any other cruft that ar won't like
         * We also need to explode any libraries listed
         */

        for (a=0; a < cmd_data->num_args; a++) {
            arg = cmd_data->arglist[a];

            if (arg) {
                ext = strrchr(arg, '.');

                if (ext) {
                    ext++;
                }

                if (arg[0] == '-') {
                    cmd_data->arglist[a] = NULL;

                    if (strcmp(arg, "-rpath") == 0 && a+1 < cmd_data->num_args) {
                        cmd_data->arglist[a+1] = NULL;
                    }

                    if (strcmp(arg, "-R") == 0 && a+1 < cmd_data->num_args) {
                        cmd_data->arglist[a+1] = NULL;
                    }

                    if (strcmp(arg, "-version-info") == 0 && a+1 < cmd_data->num_args) {
                        cmd_data->arglist[a+1] = NULL;
                    }

                    if (strcmp(arg, "-Zstack") == 0 && a+1 < cmd_data->num_args) {
                        cmd_data->arglist[a+1] = NULL;
                    }

                    if (strcmp(arg, "-o") == 0) {
                        a++;
                    }
                }

                if (strcmp(arg, CC) == 0 || strcmp(arg, CC EXE_EXT) == 0) {
                    cmd_data->arglist[a] = LIBRARIAN " cr";
                }

                if (ext) {
                    if (strcmp(ext, "h") == 0 || strcmp(ext, "c") == 0) {
                        /* ignore source files, they don't belong in a library */
                        cmd_data->arglist[a] = NULL;
                    }

                    if (strcmp(ext, STATIC_LIB_EXT) == 0) {
                        cmd_data->arglist[a] = NULL;
                        explode_static_lib(arg, cmd_data);
                    }
                }
            }
        }
    }

    if (cmd_data->output_type == otDynamicLibrary) {
        for (a=0; a < cmd_data->num_args; a++) {
            arg = cmd_data->arglist[a];

            if (arg) {
                if (strcmp(arg, "-rpath") == 0 && a+1 < cmd_data->num_args) {
                    cmd_data->arglist[a] = NULL;
                    cmd_data->arglist[a+1] = NULL;
                }
            }
        }

        if (export_all) {
            generate_def_file(cmd_data);
        }
    }

#if USE_OMF
    if (cmd_data->output_type == otObject ||
        cmd_data->output_type == otProgram ||
        cmd_data->output_type == otDynamicLibrary) {
        cmd_data->arglist[cmd_data->num_args++] = "-Zomf";
    }
#endif

    if (shared && (cmd_data->output_type == otObject || cmd_data->output_type == otDynamicLibrary)) {
        cmd_data->arglist[cmd_data->num_args++] = SHARE_SW;
    }
}