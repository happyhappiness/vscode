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

    ext = strrchr(apr_filename_of_pathname(cmd_only), '.');
    
    if (*ext == '.')
        ++ext;

    /* If it is an NLM then just execute it. */
    if (stricmp(ext, "nlm")) {
        *cmd = apr_table_get(d->file_type_handlers, ext);
        if (*cmd == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Could not find a command associated with the %s extension", ext);
            return APR_EBADF;
        }
        detached = apr_table_get(d->file_handler_mode, ext);
        if (detached) {
            e_info->detached = 1;
        }
    }

    apr_tokenize_to_argv(*cmd, (char***)argv, p);
    e_info->cmd_type = APR_PROGRAM;
    *cmd = ap_server_root_relative(p, cmd_only);

    return APR_SUCCESS;
}