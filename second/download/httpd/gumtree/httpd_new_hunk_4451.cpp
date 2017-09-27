    }
    else {
        len = alias_match(r->uri, fake);

        if (len != 0) {
            if ((real[0] == '!') && (real[1] == '\0')) {
                ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(03463)
                              "proxying is explicitly disabled for URI path "
                              "'%s'; declining", r->uri);
                return DECLINED;
            }
            if (nocanon && len != alias_match(r->unparsed_uri, ent->fake)) {
                mismatch = 1;
                use_uri = r->uri;
            }
