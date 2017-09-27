                 * which may be confusing.
                 */
                if (found && strcmp(found, ent[i].real)) {
                    found = apr_pstrcat(r->pool, "proxy:", found, NULL);
                }
                else {
                    found = apr_pstrcat(r->pool, "proxy:", ent[i].real,
                                        use_uri, NULL);
                }
            }
        }
        else {
            len = alias_match(r->uri, ent[i].fake);

            if (len > 0) {
                if ((ent[i].real[0] == '!') && (ent[i].real[1] == '\0')) {
                    return DECLINED;
                }
                if (nocanon
                    && len != alias_match(r->unparsed_uri, ent[i].fake)) {
                    mismatch = 1;
                    use_uri = r->uri;
                }
                found = apr_pstrcat(r->pool, "proxy:", ent[i].real,
                                    use_uri + len, NULL);
            }
        }
        if (mismatch) {
            /* We made a reducing transformation, so we can't safely use
             * unparsed_uri.  Safe fallback is to ignore nocanon.
             */
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "Unescaped URL path matched ProxyPass; ignoring unsafe nocanon");
        }

        if (found) {
            r->filename = found;
            r->handler = "proxy-server";
            r->proxyreq = PROXYREQ_REVERSE;
            if (nocanon && !mismatch) {
                /* mod_proxy_http needs to be told.  Different module. */
                apr_table_setn(r->notes, "proxy-nocanon", "1");
            }
            return OK;
        }
    }
    return DECLINED;
}

