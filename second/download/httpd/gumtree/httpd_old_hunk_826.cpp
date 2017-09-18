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

static void register_hooks(apr_pool_t *p)
{
