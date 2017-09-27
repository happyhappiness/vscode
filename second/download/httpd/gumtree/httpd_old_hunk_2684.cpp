    f->ctx = fctx;
    return OK;
}
static int filter_lookup(ap_filter_t *f, ap_filter_rec_t *filter)
{
    ap_filter_provider_t *provider;
    int match;
    int err = 0;
    unsigned int proto_flags;
    request_rec *r = f->r;
    harness_ctx *ctx = f->ctx;
    provider_ctx *pctx;
#ifndef NO_PROTOCOL
    mod_filter_ctx *rctx = ap_get_module_config(r->request_config,
                                                &filter_module);
#endif

    /* Check registered providers in order */
    for (provider = filter->providers; provider; provider = provider->next) {
        match = ap_expr_eval(r, provider->expr, &err, NULL, ap_expr_string, NULL);
        if (err) {
            /* log error but accept match value ? */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Error evaluating filter dispatch condition");
        }

        if (match) {
            /* condition matches this provider */
#ifndef NO_PROTOCOL
            /* check protocol
