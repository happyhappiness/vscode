        ++ext;

    /* check if we have a registered command for the extension*/
    new_cmd = apr_table_get(d->file_type_handlers, ext);
    e_info->detached = 1;
    if (new_cmd == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "Could not find a command associated with the %s extension", ext);
        return APR_EBADF;
    }
    if (stricmp(new_cmd, "OS")) {
        /* If we have a registered command then add the file that was passed in as a
          parameter to the registered command. */
