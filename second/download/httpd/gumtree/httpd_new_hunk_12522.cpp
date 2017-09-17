            }
            if (!printing) {
                continue;
            }
            if (!strcmp(directive, "exec")) {
                if (noexec) {
                    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                                "httpd: exec used but not allowed in %s",
                                r->filename);
                    if (printing) {
                        ap_rputs(error, r);
                    }
                    ret = find_string(f, ENDING_SEQUENCE, r, 0);
