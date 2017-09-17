#ifdef USE_PERL_SSI
            else if (!strcmp(directive, "perl")) {
                ret = handle_perl(f, r, error);
            }
#endif
            else {
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                            "httpd: unknown directive \"%s\" "
                            "in parsed doc %s",
                            directive, r->filename);
                if (printing) {
                    ap_rputs(error, r);
                }
                ret = find_string(f, ENDING_SEQUENCE, r, 0);
            }
            if (ret) {
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                            "httpd: premature EOF in parsed file %s",
                            r->filename);
                return;
            }
        }
        else {
