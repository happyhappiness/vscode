                has_content = 1;
            }
            else if (!strncmp(buffer, "content-length:", 15)) {
                char *errp;
                apr_off_t number;

                if (apr_strtoff(&number, body, &errp, 10)
                    || *errp || number < 0) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Parse error in type map, Content-Length: "
                                  "'%s' in %s is invalid.",
                                  body, r->filename);
                    break;
                }
                mime_info.bytes = number;
                has_content = 1;
            }
            else if (!strncmp(buffer, "content-language:", 17)) {
