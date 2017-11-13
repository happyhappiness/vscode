ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "dir_walk error, could not determine the root "
                          "path of filename %s%s for uri %s",
                          r->filename, r->path_info, r->uri);