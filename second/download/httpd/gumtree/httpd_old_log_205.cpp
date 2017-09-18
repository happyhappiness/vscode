ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                              "unknown directive \"%s\" in parsed doc %s",
                              ctx->combined_tag, r->filename);