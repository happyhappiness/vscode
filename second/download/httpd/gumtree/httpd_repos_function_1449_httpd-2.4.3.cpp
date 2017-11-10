static int handle_multi(request_rec *r)
{
    negotiation_state *neg;
    var_rec *best, *avail_recs;
    request_rec *sub_req;
    int res;
    int j;

    if (r->finfo.filetype != APR_NOFILE
        || !(ap_allow_options(r) & OPT_MULTI)) {
        return DECLINED;
    }

    neg = parse_accept_headers(r);

    if ((res = read_types_multi(neg))) {
      return_from_multi:
        /* free all allocated memory from subrequests */
        avail_recs = (var_rec *) neg->avail_vars->elts;
        for (j = 0; j < neg->avail_vars->nelts; ++j) {
            var_rec *variant = &avail_recs[j];
            if (variant->sub_req) {
                ap_destroy_sub_req(variant->sub_req);
            }
        }
        return res;
    }
    if (neg->avail_vars->nelts == 0) {
        return DECLINED;
    }

    res = do_negotiation(r, neg, &best,
                         (r->method_number != M_GET) || r->args ||
                         (r->path_info && *r->path_info));
    if (res != 0)
        goto return_from_multi;

    if (!(sub_req = best->sub_req)) {
        /* We got this out of a map file, so we don't actually have
         * a sub_req structure yet.  Get one now.
         */

        sub_req = ap_sub_req_lookup_file(best->file_name, r, r->output_filters);
        if (sub_req->status != HTTP_OK) {
            res = sub_req->status;
            ap_destroy_sub_req(sub_req);
            goto return_from_multi;
        }
    }
    if (sub_req->args == NULL) {
        sub_req->args = r->args;
    }

    /* now do a "fast redirect" ... promotes the sub_req into the main req */
    ap_internal_fast_redirect(sub_req, r);

    /* give no advise for time on this subrequest.  Perhaps we
     * should tally the last mtime amoung all variants, and date
     * the most recent, but that could confuse the proxies.
     */
    r->mtime = 0;

    /* clean up all but our favorite variant, since that sub_req
     * is now merged into the main request!
     */
    avail_recs = (var_rec *) neg->avail_vars->elts;
    for (j = 0; j < neg->avail_vars->nelts; ++j) {
        var_rec *variant = &avail_recs[j];
        if (variant != best && variant->sub_req) {
            ap_destroy_sub_req(variant->sub_req);
        }
    }
    return OK;
}