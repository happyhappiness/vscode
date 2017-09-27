                char *tag = apr_pstrdup(neg->pool, body);
                char *eol = strchr(tag, '\0');
                apr_size_t len = MAX_STRING_LEN;
                while (--eol >= tag && apr_isspace(*eol))
                    *eol = '\0';
                if ((mime_info.body = get_body(buffer, &len, tag, *map)) < 0) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Syntax error in type map, no end tag '%s'"
                                  "found in %s for Body: content.",
                                  tag, r->filename);
                     break;
                }
                mime_info.bytes = len;
