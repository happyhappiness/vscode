r(APLOG_MARK, APLOG_ERR|APLOG_TOCLIENT, 0, r,
                          "%s: %s", malformed,
                          apr_filepath_name_get(r->filename));