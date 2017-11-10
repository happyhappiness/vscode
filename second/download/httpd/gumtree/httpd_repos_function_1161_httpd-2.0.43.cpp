static int include_cgi(char *s, request_rec *r, ap_filter_t *next,
                       apr_bucket *head_ptr, apr_bucket **inserted_head)
{
    request_rec *rr = ap_sub_req_lookup_uri(s, r, next);
    int rr_status;
    apr_bucket  *tmp_buck, *tmp2_buck;

    if (rr->status != HTTP_OK) {
        ap_destroy_sub_req(rr);
        return -1;
    }

    /* No hardwired path info or query allowed */

    if ((rr->path_info && rr->path_info[0]) || rr->args) {
        ap_destroy_sub_req(rr);
        return -1;
    }
    if (rr->finfo.filetype != APR_REG) {
        ap_destroy_sub_req(rr);
        return -1;
    }

    /* Script gets parameters of the *document*, for back compatibility */

    rr->path_info = r->path_info;       /* hard to get right; see mod_cgi.c */
    rr->args = r->args;

    /* Force sub_req to be treated as a CGI request, even if ordinary
     * typing rules would have called it something else.
     */
    ap_set_content_type(rr, CGI_MAGIC_TYPE);

    /* Run it. */

    rr_status = ap_run_sub_req(rr);
    if (ap_is_HTTP_REDIRECT(rr_status)) {
        apr_size_t len_loc;
        const char *location = apr_table_get(rr->headers_out, "Location");
        conn_rec *c = r->connection;

        location = ap_escape_html(rr->pool, location);
        len_loc = strlen(location);

        /* XXX: if most of this stuff is going to get copied anyway,
         * it'd be more efficient to pstrcat it into a single pool buffer
         * and a single pool bucket */

        tmp_buck = apr_bucket_immortal_create("<A HREF=\"",
                                              sizeof("<A HREF=\"") - 1,
                                              c->bucket_alloc);
        APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
        tmp2_buck = apr_bucket_heap_create(location, len_loc, NULL,
                                           c->bucket_alloc);
        APR_BUCKET_INSERT_BEFORE(head_ptr, tmp2_buck);
        tmp2_buck = apr_bucket_immortal_create("\">", sizeof("\">") - 1,
                                               c->bucket_alloc);
        APR_BUCKET_INSERT_BEFORE(head_ptr, tmp2_buck);
        tmp2_buck = apr_bucket_heap_create(location, len_loc, NULL,
                                           c->bucket_alloc);
        APR_BUCKET_INSERT_BEFORE(head_ptr, tmp2_buck);
        tmp2_buck = apr_bucket_immortal_create("</A>", sizeof("</A>") - 1,
                                               c->bucket_alloc);
        APR_BUCKET_INSERT_BEFORE(head_ptr, tmp2_buck);

        if (*inserted_head == NULL) {
            *inserted_head = tmp_buck;
        }
    }

    ap_destroy_sub_req(rr);

    return 0;
}