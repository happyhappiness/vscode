     *     ISAPICacheFile myapp.dll anotherapp.dll thirdapp.dll
     * </Directory>
     * would be very convienent.
     */
    fspec = ap_server_root_relative(cmd->pool, filename);
    if (!fspec) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, APR_EBADPATH, cmd->server, APLOGNO(02103)
                     "invalid module path, skipping %s", filename);
        return NULL;
    }
    if ((rv = apr_stat(&tmp, fspec, APR_FINFO_TYPE,
                      cmd->temp_pool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, cmd->server, APLOGNO(02104)
                     "unable to stat, skipping %s", fspec);
        return NULL;
    }
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

    return NULL;
}

