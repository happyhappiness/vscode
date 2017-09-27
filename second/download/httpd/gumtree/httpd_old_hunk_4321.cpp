    if (tmp.filetype != APR_REG) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(02105)
                     "not a regular file, skipping %s", fspec);
        return NULL;
    }

    /* Load the extention as cached (with null request_rec) */
    rv = isapi_lookup(cmd->pool, cmd->server, NULL, fspec, &isa);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, cmd->server, APLOGNO(02106)
                     "unable to cache, skipping %s", fspec);
        return NULL;
    }
