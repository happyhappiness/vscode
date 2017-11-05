static ap_filter_t *add_any_filter_handle(ap_filter_rec_t *frec, void *ctx,
                                          request_rec *r, conn_rec *c,
                                          ap_filter_t **r_filters,
                                          ap_filter_t **p_filters,
                                          ap_filter_t **c_filters)
{
    apr_pool_t *p = frec->ftype < AP_FTYPE_CONNECTION && r ? r->pool : c->pool;
    ap_filter_t *f = apr_palloc(p, sizeof(*f));
    ap_filter_t **outf;

    if (frec->ftype < AP_FTYPE_PROTOCOL) {
        if (r) {
            outf = r_filters;
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                      "a content filter was added without a request: %s", frec->name);
            return NULL;
        }
    }
    else if (frec->ftype < AP_FTYPE_CONNECTION) {
        if (r) {
            outf = p_filters;
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                         "a protocol filter was added without a request: %s", frec->name);
            return NULL;
        }
    }
    else {
        outf = c_filters;
    }

    f->frec = frec;
    f->ctx = ctx;
    /* f->r must always be NULL for connection filters */
    f->r = frec->ftype < AP_FTYPE_CONNECTION ? r : NULL;
    f->c = c;
    f->next = NULL;

    if (INSERT_BEFORE(f, *outf)) {
        f->next = *outf;

        if (*outf) {
            ap_filter_t *first = NULL;

            if (r) {
                /* If we are adding our first non-connection filter,
                 * Then don't try to find the right location, it is
                 * automatically first.
                 */
                if (*r_filters != *c_filters) {
                    first = *r_filters;
                    while (first && (first->next != (*outf))) {
                        first = first->next;
                    }
                }
            }
            if (first && first != (*outf)) {
                first->next = f;
            }
        }
        *outf = f;
    }
    else {
        ap_filter_t *fscan = *outf;
        while (!INSERT_BEFORE(f, fscan->next))
            fscan = fscan->next;

        f->next = fscan->next;
        fscan->next = f;
    }

    if (frec->ftype < AP_FTYPE_CONNECTION && (*r_filters == *c_filters)) {
        *r_filters = *p_filters;
    }
    return f;
}