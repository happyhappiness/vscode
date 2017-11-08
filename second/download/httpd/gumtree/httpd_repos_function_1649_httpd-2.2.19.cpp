static int filter_init(ap_filter_t *f)
{
    ap_filter_provider_t *p;
    provider_ctx *pctx;
    int err;
    ap_filter_rec_t *filter = f->frec;

    harness_ctx *fctx = apr_pcalloc(f->r->pool, sizeof(harness_ctx));
    for (p = filter->providers; p; p = p->next) {
        if (p->frec->filter_init_func == filter_init) {
            ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, f->c,
                          "Chaining of FilterProviders not supported");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        else if (p->frec->filter_init_func) {
            f->ctx = NULL;
            if ((err = p->frec->filter_init_func(f)) != OK) {
                ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, f->c,
                              "filter_init for %s failed", p->frec->name);
                return err;   /* if anyone errors out here, so do we */
            }
            if (f->ctx != NULL) {
                /* the filter init function set a ctx - we need to record it */
                pctx = apr_pcalloc(f->r->pool, sizeof(provider_ctx));
                pctx->provider = p;
                pctx->ctx = f->ctx;
                pctx->next = fctx->init_ctx;
                fctx->init_ctx = pctx;
            }
        }
    }
    f->ctx = fctx;
    return OK;
}