ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
                         "mod_rewrite: could not start RewriteMap "
                         "program %s", map->checkfile);