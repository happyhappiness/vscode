ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              "dir_walk error, path_info %s is not relative "
                              "to the filename path %s for uri %s",
                              r->path_info, r->filename, r->uri);