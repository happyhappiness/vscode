static void fixup_rules(saxctxt *ctx)
{
    urlmap *newp;
    urlmap *p;
    urlmap *prev = NULL;
    request_rec *r = ctx->f->r;

    for (p = ctx->cfg->map; p; p = p->next) {
        if (p->cond != NULL) {
            const char *err;
            int ok = ap_expr_exec(r, p->cond, &err);
            if (err) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01421)
                              "Error evaluating expr: %s", err);
            }
            if (ok == 0) {
                continue;  /* condition is unsatisfied */
            }
        }

        newp = apr_pmemdup(r->pool, p, sizeof(urlmap));

        if (newp->flags & M_INTERPOLATE_FROM) {
            newp->from.c = interpolate_vars(r, newp->from.c);
            if (!newp->from.c || !*newp->from.c)
                continue;        /* don't use empty from-pattern */
            if (newp->flags & M_REGEX) {
                newp->from.r = ap_pregcomp(r->pool, newp->from.c,
                                           newp->regflags);
            }
        }
        if (newp->flags & M_INTERPOLATE_TO) {
            newp->to = interpolate_vars(r, newp->to);
        }
        /* evaluate p->cond; continue if unsatisfied */
        /* create new urlmap with memcpy and append to map */
        /* interpolate from if flagged to do so */
        /* interpolate to if flagged to do so */

        if (prev != NULL)
            prev->next = newp;
        else
            ctx->map = newp;
        prev = newp;
    }

    if (prev)
        prev->next = NULL;
}