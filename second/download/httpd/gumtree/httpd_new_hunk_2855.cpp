                has_content = 1;
            }
            else if (!strncmp(buffer, "content-length:", 15)) {
                char *errp;
                apr_off_t number;

                body1 = ap_get_token(neg->pool, &body, 0);
                if (apr_strtoff(&number, body1, &errp, 10) != APR_SUCCESS
                    || *errp || number < 0) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00684)
                                  "Parse error in type map, Content-Length: "
                                  "'%s' in %s is invalid.",
                                  body1, r->filename);
                    break;
                }
                mime_info.bytes = number;
                has_content = 1;
            }
            else if (!strncmp(buffer, "content-language:", 17)) {
