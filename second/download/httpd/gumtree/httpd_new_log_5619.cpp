r(SCRIPT_LOG_MARK, APLOG_ERR|APLOG_TOCLIENT, 0, r,
                          "malformed header from script '%s': Bad header: %.30s",
                          apr_filepath_name_get(r->filename), w);