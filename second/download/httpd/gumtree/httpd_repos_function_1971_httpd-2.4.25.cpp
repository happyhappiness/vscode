static void hc_select_exprs(request_rec *r, const char *expr)
{
    const apr_table_entry_t *elts;
    const apr_array_header_t *hdr;
    int i;
    sctx_t *ctx = (sctx_t *) ap_get_module_config(r->server->module_config,
                                                  &proxy_hcheck_module);
    if (apr_is_empty_table(ctx->conditions))
        return;

    hdr = apr_table_elts(ctx->conditions);
    elts = (const apr_table_entry_t *) hdr->elts;
    for (i = 0; i < hdr->nelts; ++i) {
        if (!elts[i].key) {
            continue;
        }
        ap_rprintf(r, "<option value='%s' %s >%s</option>\n",
                   ap_escape_html(r->pool, elts[i].key),
                   (!strcmp(elts[i].key, expr)) ? "selected" : "",
                           ap_escape_html(r->pool, elts[i].key));
    }
}