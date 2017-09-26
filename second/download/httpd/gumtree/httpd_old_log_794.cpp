ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "mod_rewrite: maximum number of internal redirects "
                      "reached. Assuming configuration error. Use "
                      "'RewriteOptions MaxRedirects' to increase the limit "
                      "if neccessary.");