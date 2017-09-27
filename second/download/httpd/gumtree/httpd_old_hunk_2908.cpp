    }
#endif

    for (m = conf->magic; m; m = m->next) {
#if MIME_MAGIC_DEBUG
        rule_counter++;
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                    MODNAME ": line=%d desc=%s", m->lineno, m->desc);
#endif

        /* check if main entry matches */
        if (!mget(r, &p, s, m, nbytes) ||
            !mcheck(r, &p, m)) {
