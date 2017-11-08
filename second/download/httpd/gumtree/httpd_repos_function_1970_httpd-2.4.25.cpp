static void hc_show_exprs(request_rec *r)
{
    const apr_table_entry_t *elts;
    const apr_array_header_t *hdr;
    int i;
    sctx_t *ctx = (sctx_t *) ap_get_module_config(r->server->module_config,
                                                  &proxy_hcheck_module);
    if (apr_is_empty_table(ctx->conditions))
        return;

    ap_rputs("\n\n<table>"
             "<tr><th colspan='2'>Health check cond. expressions:</th></tr>\n"
             "<tr><th>Expr name</th><th>Expression</th></tr>\n", r);

    hdr = apr_table_elts(ctx->conditions);
    elts = (const apr_table_entry_t *) hdr->elts;
    for (i = 0; i < hdr->nelts; ++i) {
        hc_condition_t *cond;
        if (!elts[i].key) {
            continue;
        }
        cond = (hc_condition_t *)elts[i].val;
        ap_rprintf(r, "<tr><td>%s</td><td>%s</td></tr>\n",
                   ap_escape_html(r->pool, elts[i].key),
                   ap_escape_html(r->pool, cond->expr));
    }
    ap_rputs("</table><hr/>\n", r);
}