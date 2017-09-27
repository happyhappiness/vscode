                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02910)
                              "parsing Upgrade header: %s", err);
                return DECLINED;
            }
            
            if (offers && offers->nelts > 0) {
                const char *protocol = ap_select_protocol(c, r, NULL, offers);
                if (protocol && strcmp(protocol, ap_get_protocol(c))) {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02909)
                                  "Upgrade selects '%s'", protocol);
                    /* Let the client know what we are upgrading to. */
                    apr_table_clear(r->headers_out);
                    apr_table_setn(r->headers_out, "Upgrade", protocol);
