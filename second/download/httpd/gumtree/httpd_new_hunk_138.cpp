        if (r->args && r->args[0] && !ap_strchr_c(r->args, '=')) {
            args = r->args;
        }
    }

    cmd_only = apr_pstrdup(p, *cmd);
    e_info->cmd_type = APR_PROGRAM;

    /* truncate any arguments from the cmd */
    for (ptr = cmd_only; *ptr && (*ptr != ' '); ptr++);
    *ptr = '\0';

    /* Figure out what the extension is so that we can matche it. */
    ext = strrchr(apr_filepath_name_get(cmd_only), '.');

    /* If there isn't an extension then give it an empty string */
    if (!ext) {
        ext = "";
    }
    
    /* eliminate the '.' if there is one */
    if (*ext == '.')
        ++ext;

    /* check if we have a registered command for the extension*/
    new_cmd = apr_table_get(d->file_type_handlers, ext);
    if (new_cmd == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "Could not find a command associated with the %s extension", ext);
        return APR_EBADF;
    }
    if (stricmp(new_cmd, "OS")) {
        /* If we have a registered command then add the file that was passed in as a
          parameter to the registered command. */
        *cmd = apr_pstrcat (p, new_cmd, " ", cmd_only, NULL);

        /* Run in its own address space if specified */
        detached = apr_table_get(d->file_handler_mode, ext);
        if (detached) {
            e_info->cmd_type = APR_PROGRAM_ENV;
        }
        else {
            e_info->cmd_type = APR_PROGRAM;
        }
    }

    /* Tokenize the full command string into its arguments */
    apr_tokenize_to_argv(*cmd, (char***)argv, p);
    e_info->detached = 1;

    /* The first argument should be the executible */
    *cmd = ap_server_root_relative(p, *argv[0]);

    return APR_SUCCESS;
}
