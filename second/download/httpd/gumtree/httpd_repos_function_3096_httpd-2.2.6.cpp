int run_mode(command_t *cmd_data)
{
    int rv;
    count_chars *cctemp;

    cctemp = (count_chars*)malloc(sizeof(count_chars));
    init_count_chars(cctemp);

    switch (cmd_data->mode)
    {
    case mCompile:
        rv = run_command(cmd_data, cmd_data->arglist);
        if (rv) {
            return rv;
        }
        break;
    case mInstall:
        /* Well, we'll assume it's a file going to a directory... */
        /* For brain-dead install-sh based scripts, we have to repeat
         * the command N-times.  install-sh should die.
         */
        if (!cmd_data->output_name) {
            rv = run_command(cmd_data, cmd_data->arglist);
            if (rv) {
                return rv;
            }
        }
        if (cmd_data->output_name) {
            append_count_chars(cctemp, cmd_data->arglist);
            insert_count_chars(cctemp,
                               cmd_data->output_name,
                               cctemp->num - 1);
            rv = run_command(cmd_data, cctemp);
            if (rv) {
                return rv;
            }
            clear_count_chars(cctemp);
        }
        if (cmd_data->static_name.install) {
            append_count_chars(cctemp, cmd_data->arglist);
            insert_count_chars(cctemp,
                               cmd_data->static_name.install,
                               cctemp->num - 1);
            rv = run_command(cmd_data, cctemp);
            if (rv) {
                return rv;
            }
            clear_count_chars(cctemp);
        }
        if (cmd_data->shared_name.install) {
            append_count_chars(cctemp, cmd_data->arglist);
            insert_count_chars(cctemp,
                               cmd_data->shared_name.install,
                               cctemp->num - 1);
            rv = run_command(cmd_data, cctemp);
            if (rv) {
                return rv;
            }
            clear_count_chars(cctemp);
        }
        if (cmd_data->module_name.install) {
            append_count_chars(cctemp, cmd_data->arglist);
            insert_count_chars(cctemp,
                               cmd_data->module_name.install,
                               cctemp->num - 1);
            rv = run_command(cmd_data, cctemp);
            if (rv) {
                return rv;
            }
            clear_count_chars(cctemp);
        }
        break;
    case mLink:
        if (!cmd_data->options.dry_run) {
            /* Check first to see if the dir already exists! */
            mode_t old_umask;

            old_umask = umask(0);
            umask(old_umask);

            mkdir(".libs", ~old_umask);
        }

        if (cmd_data->output == otStaticLibraryOnly ||
            cmd_data->output == otLibrary) {
#ifdef RANLIB
            const char *lib_args[3];
#endif
            /* Removes compiler! */
            cmd_data->program = LIBRARIAN;
            push_count_chars(cmd_data->program_opts, LIBRARIAN_OPTS);
            push_count_chars(cmd_data->program_opts,
                             cmd_data->static_name.normal);

            rv = run_command(cmd_data, cmd_data->obj_files);
            if (rv) {
                return rv;
            }

#ifdef RANLIB
            lib_args[0] = RANLIB;
            lib_args[1] = cmd_data->static_name.normal;
            lib_args[2] = NULL;
            external_spawn(cmd_data, RANLIB, lib_args);
#endif
        }

        if (cmd_data->output == otDynamicLibraryOnly ||
            cmd_data->output == otModule ||
            cmd_data->output == otLibrary) {
            cmd_data->program = NULL;
            clear_count_chars(cmd_data->program_opts);

            append_count_chars(cmd_data->program_opts, cmd_data->arglist);
            if (cmd_data->output != otModule) {
#ifdef SHARED_OPTS
                push_count_chars(cmd_data->program_opts, SHARED_OPTS);
#endif
#ifdef dynamic_link_version_func
                push_count_chars(cmd_data->program_opts,
                             dynamic_link_version_func(cmd_data->version_info));
#endif
            }
            if (cmd_data->output == otModule) {
#ifdef MODULE_OPTS
                push_count_chars(cmd_data->program_opts, MODULE_OPTS);
#endif
            }
#ifdef DYNAMIC_LINK_OPTS
            if (cmd_data->options.pic_mode != pic_AVOID) {
                push_count_chars(cmd_data->program_opts,
                                 DYNAMIC_LINK_OPTS);
            }
#endif
            rv = run_command(cmd_data, cmd_data->shared_opts.normal);
            if (rv) {
                return rv;
            }
        }
        if (cmd_data->output == otProgram) {
            rv = run_command(cmd_data, cmd_data->arglist);
            if (rv) {
                return rv;
            }
        }
        break;
    default:
        break;
    } 

    return 0;
}