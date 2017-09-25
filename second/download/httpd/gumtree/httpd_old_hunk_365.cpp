    
    /* eliminate the '.' if there is one */
    if (*ext == '.')
        ++ext;

    /* check if we have a registered command for the extension*/
    *cmd = apr_table_get(d->file_type_handlers, ext);
    if (*cmd == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "Could not find a command associated with the %s extension", ext);
        return APR_EBADF;
    }
    if (!stricmp(*cmd, "OS")) {
        /* If it is an NLM then restore *cmd and just execute it */
        *cmd = cmd_only;
    }
    else {
        /* If we have a registered command then add the file that was passed in as a
          parameter to the registered command. */
        *cmd = apr_pstrcat (p, *cmd, " ", cmd_only, NULL);

        /* Run in its own address space if specified */
        detached = apr_table_get(d->file_handler_mode, ext);
        if (detached) {
            e_info->cmd_type = APR_PROGRAM_ENV;
        }
