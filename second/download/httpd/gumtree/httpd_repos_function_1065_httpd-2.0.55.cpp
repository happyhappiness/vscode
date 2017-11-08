static int setup_choice_response(request_rec *r, negotiation_state *neg,
                                 var_rec *variant)
{
    request_rec *sub_req;
    const char *sub_vary;

    if (!variant->sub_req) {
        int status;

        sub_req = ap_sub_req_lookup_file(variant->file_name, r, NULL);
        status = sub_req->status;

        if (status != HTTP_OK &&
            !apr_table_get(sub_req->err_headers_out, "TCN")) {
            ap_destroy_sub_req(sub_req);
            return status;
        }
        variant->sub_req = sub_req;
    }
    else {
        sub_req = variant->sub_req;
    }

    /* The variant selection algorithm told us to return a "Choice"
     * response. This is the normal variant response, with
     * some extra headers. First, ensure that the chosen
     * variant did or will not itself engage in transparent negotiation.
     * If not, set the appropriate headers, and fall through to
     * the normal variant handling
     */

    /* This catches the error that a transparent type map selects a
     * transparent multiviews resource as the best variant.
     *
     * XXX: We do not signal an error if a transparent type map
     * selects a _non_transparent multiviews resource as the best
     * variant, because we can generate a legal negotiation response
     * in this case.  In this case, the vlist_validator of the
     * nontransparent subrequest will be lost however.  This could
     * lead to cases in which a change in the set of variants or the
     * negotiation algorithm of the nontransparent resource is never
     * propagated up to a HTTP/1.1 cache which interprets Vary.  To be
     * completely on the safe side we should return HTTP_VARIANT_ALSO_VARIES
     * for this type of recursive negotiation too.
     */
    if (neg->is_transparent &&
        apr_table_get(sub_req->err_headers_out, "TCN")) {
        return HTTP_VARIANT_ALSO_VARIES;
    }

    /* This catches the error that a transparent type map recursively
     * selects, as the best variant, another type map which itself
     * causes transparent negotiation to be done.
     *
     * XXX: Actually, we catch this error by catching all cases of
     * type map recursion.  There are some borderline recursive type
     * map arrangements which would not produce transparent
     * negotiation protocol errors or lack of cache propagation
     * problems, but such arrangements are very hard to detect at this
     * point in the control flow, so we do not bother to single them
     * out.
     *
     * Recursive type maps imply a recursive arrangement of negotiated
     * resources which is visible to outside clients, and this is not
     * supported by the transparent negotiation caching protocols, so
     * if we are to have generic support for recursive type maps, we
     * have to create some configuration setting which makes all type
     * maps non-transparent when recursion is enabled.  Also, if we
     * want recursive type map support which ensures propagation of
     * type map changes into HTTP/1.1 caches that handle Vary, we
     * would have to extend the current mechanism for generating
     * variant list validators.
     */
    if (sub_req->handler && strcmp(sub_req->handler, "type-map") == 0) {
        return HTTP_VARIANT_ALSO_VARIES;
    }

    /* This adds an appropriate Variant-Vary header if the subrequest
     * is a multiviews resource.
     *
     * XXX: TODO: Note that this does _not_ handle any Vary header
     * returned by a CGI if sub_req is a CGI script, because we don't
     * see that Vary header yet at this point in the control flow.
     * This won't cause any cache consistency problems _unless_ the
     * CGI script also returns a Cache-Control header marking the
     * response as cachable.  This needs to be fixed, also there are
     * problems if a CGI returns an Etag header which also need to be
     * fixed.
     */
    if ((sub_vary = apr_table_get(sub_req->err_headers_out, "Vary")) != NULL) {
        apr_table_setn(r->err_headers_out, "Variant-Vary", sub_vary);

        /* Move the subreq Vary header into the main request to
         * prevent having two Vary headers in the response, which
         * would be legal but strange.
         */
        apr_table_setn(r->err_headers_out, "Vary", sub_vary);
        apr_table_unset(sub_req->err_headers_out, "Vary");
    }

    apr_table_setn(r->err_headers_out, "Content-Location",
                  apr_pstrdup(r->pool, variant->file_name));

    set_neg_headers(r, neg, alg_choice);         /* add Alternates and Vary */

    /* Still to do by caller: add Expires */

    return 0;
}