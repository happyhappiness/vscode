ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, data->r,
                              "Timeout waiting for output from CGI script %s",
                              data->r->filename);