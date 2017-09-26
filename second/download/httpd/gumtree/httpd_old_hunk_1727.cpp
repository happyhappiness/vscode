                 * which may be confusing.
                 */
                if (found && strcmp(found, ent[i].real)) {
                    found = apr_pstrcat(r->pool, "proxy:", found, NULL);
                }
                else {
                    found = apr_pstrcat(r->pool, "proxy:", ent[i].real, r->uri,
                                        NULL);
                }
            }
        }
        else {
            len = alias_match(r->uri, ent[i].fake);

            if (len > 0) {
                if ((ent[i].real[0] == '!') && (ent[i].real[1] == '\0')) {
                    return DECLINED;
                }

                found = apr_pstrcat(r->pool, "proxy:", ent[i].real,
                                    r->uri + len, NULL);
            }
        }
        if (found) {
            r->filename = found;
            r->handler = "proxy-server";
            r->proxyreq = PROXYREQ_REVERSE;
            return OK;
        }
    }
    return DECLINED;
}

