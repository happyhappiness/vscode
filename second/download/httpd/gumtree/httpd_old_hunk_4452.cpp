            /* mod_proxy_http needs to be told.  Different module. */
            apr_table_setn(r->notes, "proxy-nocanon", "1");
        }
        if (ent->flags & PROXYPASS_NOQUERY) {
            apr_table_setn(r->notes, "proxy-noquery", "1");
        }
        return OK;
    }

    return DONE;
}

