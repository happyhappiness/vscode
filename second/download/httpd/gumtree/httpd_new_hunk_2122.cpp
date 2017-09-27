                          dc->charset_default ? dc->charset_default : "unspecified");
        }
        return DECLINED;
    }

    /* catch proxy requests */
    if (r->proxyreq) {
        return DECLINED;
    }

    /* mod_rewrite indicators */
    if (r->filename
        && (!strncmp(r->filename, "redirect:", 9)
            || !strncmp(r->filename, "gone:", 5)
            || !strncmp(r->filename, "passthrough:", 12)
            || !strncmp(r->filename, "forbidden:", 10))) {
        return DECLINED;
    }

    /* no translation when server and network charsets are set to the same value */
    if (!strcasecmp(dc->charset_source, dc->charset_default)) {
        return DECLINED;
    }

    /* Get storage for the request data and the output filter context.
     * We rarely need the input filter context, so allocate that separately.
     */
    reqinfo = (charset_req_t *)apr_pcalloc(r->pool,
