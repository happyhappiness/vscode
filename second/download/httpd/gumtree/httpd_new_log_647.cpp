ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown value "
                              "\"%s\" to parameter \"sizefmt\" of tag config "
                              "in %s", parsed_string, r->filename);