            /* mod_proxy_http needs to be told.  Different module. */
            apr_table_setn(r->notes, "proxy-nocanon", "1");
        }
        if (ent->flags & PROXYPASS_NOQUERY) {
            apr_table_setn(r->notes, "proxy-noquery", "1");
        }

        ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(03464)
                      "URI path '%s' matches proxy handler '%s'", r->uri,
                      found);

        return OK;
    }

    return DONE;
}

