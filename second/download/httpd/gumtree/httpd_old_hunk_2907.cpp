#if MIME_MAGIC_DEBUG
    for (m = conf->magic; m; m = m->next) {
        if (apr_isprint((((unsigned long) m) >> 24) & 255) &&
            apr_isprint((((unsigned long) m) >> 16) & 255) &&
            apr_isprint((((unsigned long) m) >> 8) & 255) &&
            apr_isprint(((unsigned long) m) & 255)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                        MODNAME ": match: POINTER CLOBBERED! "
                        "m=\"%c%c%c%c\"",
                        (((unsigned long) m) >> 24) & 255,
                        (((unsigned long) m) >> 16) & 255,
                        (((unsigned long) m) >> 8) & 255,
                        ((unsigned long) m) & 255);
