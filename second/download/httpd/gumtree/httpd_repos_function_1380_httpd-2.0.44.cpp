static apr_status_t ap_cgi_build_command(const char **cmd, const char ***argv,
                                         request_rec *r, apr_pool_t *p, 
                                         cgi_exec_info_t *e_info)
{
    char *ext = NULL;
    char *cmd_only, *ptr;
    const char *detached = NULL;
    netware_dir_config *d;
    apr_file_t *fh;
    const char *args = "";

    d = (netware_dir_config *)ap_get_module_config(r->per_dir_config, 
                                               &netware_module);

    if (e_info->process_cgi) {
        /* Handle the complete file name, we DON'T want to follow suexec, since
         * an unrooted command is as predictable as shooting craps in Win32.
         *
         * Notice that unlike most mime extension parsing, we have to use the
         * win32 parsing here, therefore the final extension is the only one
         * we will consider
         */
        *cmd = r->filename;
        if (r->args && r->args[0] && !ap_strchr_c(r->args, '=')) {
            args = r->args;
        }
    }

    cmd_only = apr_pstrdup(p, *cmd);

    /* truncate any arguments from the cmd */
    for (ptr = cmd_only; *ptr && (*ptr != ' '); ptr++);
    *ptr = '\0';

    /* Figure out what the extension is so that we can matche it. */
    ext = strrchr(apr_filename_of_pathname(cmd_only), '.');
    
    /* eliminate the '.' if there is one */
    if (*ext == '.')
        ++ext;

    /* If it is an NLM then just execute it. */
    if (stricmp(ext, "nlm")) {
        /* check if we have a registered command for the extension*/
        *cmd = apr_table_get(d->file_type_handlers, ext);
        if (*cmd == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Could not find a command associated with the %s extension", ext);
            return APR_EBADF;
        }

        /* If we have a registered command then add the file that was passed in as a
          parameter to the registered command. */
        *cmd = apr_pstrcat (p, *cmd, " ", cmd_only, NULL);

        /* Run in its own address space if specified */
        detached = apr_table_get(d->file_handler_mode, ext);
        if (detached) {
            e_info->detached = 1;
        }
    }

    /* Tokenize the full command string into its arguments */
    apr_tokenize_to_argv(*cmd, (char***)argv, p);
    e_info->cmd_type = APR_PROGRAM;

    /* The first argument should be the executible */
    *cmd = ap_server_root_relative(p, *argv[0]);

    return APR_SUCCESS;
}