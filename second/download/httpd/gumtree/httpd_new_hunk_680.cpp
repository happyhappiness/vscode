    if (!fspec) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, APR_EBADPATH, cmd->server,
                     "mod_file_cache: invalid file path "
                     "%s, skipping", filename);
	return;
    }
    if ((rc = apr_stat(&tmp.finfo, fspec, APR_FINFO_MIN,
                                 cmd->temp_pool)) != APR_SUCCESS) {
	ap_log_error(APLOG_MARK, APLOG_WARNING, rc, cmd->server,
	    "mod_file_cache: unable to stat(%s), skipping", fspec);
	return;
    }
    if (tmp.finfo.filetype != APR_REG) {
