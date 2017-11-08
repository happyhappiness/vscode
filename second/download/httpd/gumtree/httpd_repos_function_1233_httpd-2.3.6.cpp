static int fixup_dflt(request_rec *r)
{
    dir_config_rec *d = ap_get_module_config(r->per_dir_config, &dir_module);
    const char *name_ptr;
    request_rec *rr;
    int error_notfound = 0;
    if ((r->finfo.filetype != APR_NOFILE) || (r->handler != NULL)) {
        return DECLINED;
    }
    name_ptr = d->dflt;
    if (name_ptr == NULL) {
        return DECLINED;
    }
    /* XXX: if FallbackResource points to something that doesn't exist,
     * this may recurse until it hits the limit for internal redirects
     * before returning an Internal Server Error.
     */

    /* The logic of this function is basically cloned and simplified
     * from fixup_dir below.  See the comments there.
     */
    if (r->args != NULL) {
        name_ptr = apr_pstrcat(r->pool, name_ptr, "?", r->args, NULL);
    }
    rr = ap_sub_req_lookup_uri(name_ptr, r, r->output_filters);
    if (rr->status == HTTP_OK
        && (   (rr->handler && !strcmp(rr->handler, "proxy-server"))
            || rr->finfo.filetype == APR_REG)) {
        ap_internal_fast_redirect(rr, r);
        return OK;
    }
    else if (ap_is_HTTP_REDIRECT(rr->status)) {

        apr_pool_join(r->pool, rr->pool);
        r->notes = apr_table_overlay(r->pool, r->notes, rr->notes);
        r->headers_out = apr_table_overlay(r->pool, r->headers_out,
                                           rr->headers_out);
        r->err_headers_out = apr_table_overlay(r->pool, r->err_headers_out,
                                               rr->err_headers_out);
        error_notfound = rr->status;
    }
    else if (rr->status && rr->status != HTTP_NOT_FOUND
             && rr->status != HTTP_OK) {
        error_notfound = rr->status;
    }

    ap_destroy_sub_req(rr);
    if (error_notfound) {
        return error_notfound;
    }

    /* nothing for us to do, pass on through */
    return DECLINED;
}