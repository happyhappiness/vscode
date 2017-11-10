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
#if defined(__APPLE__) && defined(RANLIB)
            /* From the Apple libtool(1) manpage on Tiger/10.4:
             * ----
             * With  the way libraries used to be created, errors were possible
             * if the library was modified with ar(1) and  the  table  of
             * contents  was  not updated  by  rerunning ranlib(1).  Thus the
             * link editor, ld, warns when the modification date of a library
             * is more  recent  than  the  creation date  of its table of
             * contents.  Unfortunately, this means that you get the warning
             * even if you only copy the library.
             * ----
             *
             * This means that when we install the static archive, we need to
             * rerun ranlib afterwards.
             */
            const char *lib_args[3], *static_lib_name;
            char *tmp;
            size_t len1, len2;
            len1 = strlen(cmd_data->arglist->vals[cmd_data->arglist->num - 1]);

            static_lib_name = jlibtool_basename(cmd_data->static_name.install);
            len2 = strlen(static_lib_name);

            tmp = malloc(len1 + len2 + 2);

            snprintf(tmp, len1 + len2 + 2, "%s/%s",
                    cmd_data->arglist->vals[cmd_data->arglist->num - 1],
                    static_lib_name);

            lib_args[0] = RANLIB;
            lib_args[1] = tmp;
            lib_args[2] = NULL;
            external_spawn(cmd_data, RANLIB, lib_args);
            free(tmp);
#endif
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
            safe_mkdir(".libs");
        }

        if (cmd_data->output == 