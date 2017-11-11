int parse_input_file_name(char *arg, command_t *cmd_data)
{
    char *ext = strrchr(arg, '.');
    char *name = strrchr(arg, '/');
    int pathlen;
    enum lib_type libtype;
    char *newarg;

    if (!ext) {
        return 0;
    }

    ext++;

    if (name == NULL) {
        name = strrchr(arg, '\\');

        if (name == NULL) {
            name = arg;
        } else {
            name++;
        }
    } else {
        name++;
    }

    pathlen = name - arg;

    if (strcmp(ext, "lo") == 0) {
        newarg = check_object_exists(cmd_data, arg, ext - arg);
        if (!newarg) {
            printf("Can not find suitable object file for %s\n", arg);
            exit(1);
        }
        if (cmd_data->mode != mLink) {
            push_count_chars(cmd_data->arglist, newarg);
        }
        else {
            push_count_chars(cmd_data->obj_files, newarg);
        }
        return 1;
    }

    if (strcmp(ext, "la") == 0) {
        switch (cmd_data->mode) {
        case mLink:
            /* Try the .libs dir first! */
            newarg = check_library_exists(cmd_data, arg, pathlen, 1, &libtype);
            if (!newarg) {
                /* Try the normal dir next. */
                newarg = check_library_exists(cmd_data, arg, pathlen, 0, &libtype);
                if (!newarg) {
                    printf("Can not find suitable library for %s\n", arg);
                    exit(1);
                }
            }

            /* It is not ok to just add the file: a library may added with:
               1 - -L path library_name. (For *.so in Linux).
               2 - library_name.
             */
#ifdef ADD_MINUS_L
            if (libtype == type_DYNAMIC_LIB) {
                 add_minus_l(cmd_data->shared_opts.dependencies, newarg);
            } else {
                 push_count_chars(cmd_data->shared_opts.dependencies, newarg);
            }
#else
            push_count_chars(cmd_data->shared_opts.dependencies, newarg);
#endif
            if (libtype == type_DYNAMIC_LIB) {
                if (cmd_data->options.no_install) {
#ifdef RPATH
                    add_rpath_noinstall(cmd_data->shared_opts.dependencies,
                                        arg, pathlen);
#endif
#ifdef DYNAMIC_LINK_NO_INSTALL
                    /*
                     * This doesn't work as Darwin's linker has no way to
                     * override at link-time the search paths for a
                     * non-installed library.
                     */
                    /*
                    add_dylink_noinstall(cmd_data->shared_opts.dependencies,
                                         arg, pathlen, ext - arg);
                    */
#endif
                }
                else {
#ifdef RPATH
                    add_rpath_file(cmd_data->shared_opts.dependencies, arg);
#endif
                }
            }
            break;
        case mInstall:
            /* If we've already recorded a library to install, we're most
             * likely getting the .la file that we want to install as.
             * The problem is that we need to add it as the directory,
             * not the .la file itself.  Otherwise, we'll do odd things.
             */
            if (cmd_data->output == otLibrary) {
                arg[pathlen] = '\0';
                push_count_chars(cmd_data->arglist, arg);
            }
            else {
                cmd_data->output = otLibrary;
                cmd_data->output_name = arg;
                cmd_data->static_name.install = gen_install_name(arg, 0);
                cmd_data->shared_name.install = gen_install_name(arg, 1);
                cmd_data->module_name.install = gen_install_name(arg, 2);
            }
            break;
        default:
            break;
        }
        return 1;
    }

    if (strcmp(ext, "c") == 0) {
        /* If we don't already have an idea what our output name will be. */
        if (cmd_data->basename == NULL) {
            cmd_data->basename = (char *)malloc(strlen(arg) + 4);
            strcpy(cmd_data->basename, arg);
            strcpy(strrchr(cmd_data->basename, '.') + 1, "lo");

            cmd_data->fake_output_name = strrchr(cmd_data->basename, '/');
            if (cmd_data->fake_output_name) {
                cmd_data->fake_output_name++;
            }
            else {
                cmd_data->fake_output_name = cmd_data->basename;
            }
        }
    }

    return 0;
}