        m->flag |= INDIR;
    }

    /* get offset, then skip over it */
    m->offset = (int) strtol(l, &t, 0);
    if (l == t) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, serv,
                    MODNAME ": offset %s invalid", l);
    }
    l = t;

    if (m->flag & INDIR) {
        m->in.type = LONG;
