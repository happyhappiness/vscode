static negotiation_state *parse_accept_headers(request_rec *r)
{
    negotiation_state *new =
        (negotiation_state *) apr_pcalloc(r->pool, sizeof(negotiation_state));
    accept_rec *elts;
    apr_table_t *hdrs = r->headers_in;
    int i;

    new->pool = r->pool;
    new->r = r;
    new->conf = (neg_dir_config *)ap_get_module_config(r->per_dir_config,
                                                       &negotiation_module);

    new->dir_name = ap_make_dirstr_parent(r->pool, r->filename);

    new->accepts = do_header_line(r->pool, apr_table_get(hdrs, "Accept"));

    /* calculate new->accept_q value */
    if (new->accepts) {
        elts = (accept_rec *) new->accepts->elts;

        for (i = 0; i < new->accepts->nelts; ++i) {
            if (elts[i].quality < 1.0) {
                new->accept_q = 1;
            }
        }
    }

    new->accept_encodings =
        do_header_line(r->pool, apr_table_get(hdrs, "Accept-Encoding"));
    new->accept_langs =
        do_header_line(r->pool, apr_table_get(hdrs, "Accept-Language"));
    new->accept_charsets =
        do_header_line(r->pool, apr_table_get(hdrs, "Accept-Charset"));

    /* This is possibly overkill for some servers, heck, we have 
     * only 33 index.html variants in docs/docroot (today).
     * Make this configurable?
     */
    new->avail_vars = apr_array_make(r->pool, 40, sizeof(var_rec));

    return new;
}