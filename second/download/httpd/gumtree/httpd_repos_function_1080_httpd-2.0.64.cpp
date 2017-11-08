static int do_negotiation(request_rec *r, negotiation_state *neg,
                          var_rec **bestp, int prefer_scripts)
{
    var_rec *avail_recs = (var_rec *) neg->avail_vars->elts;
    int alg_result;              /* result of variant selection algorithm */
    int res;
    int j;

    /* Decide if resource is transparently negotiable */

    /* GET or HEAD? (HEAD has same method number as GET) */
    if (r->method_number == M_GET) {

        /* maybe this should be configurable, see also the comment
         * about recursive type maps in setup_choice_response()
         */
        neg->is_transparent = 1;

        /* We can't be transparent if we are a map file in the middle
         * of the request URI.
         */
        if (r->path_info && *r->path_info)
            neg->is_transparent = 0;

        for (j = 0; j < neg->avail_vars->nelts; ++j) {
            var_rec *variant = &avail_recs[j];

            /* We can't be transparent, because of internal
             * assumptions in best_match(), if there is a
             * non-neighboring variant.  We can have a non-neighboring
             * variant when processing a type map.
             */
            if (ap_strchr_c(variant->file_name, '/'))
                neg->is_transparent = 0;

            /* We can't be transparent, because of the behavior
             * of variant typemap bodies.
             */
            if (variant->body) {
                neg->is_transparent = 0;
            }
        }
    }

    if (neg->is_transparent)  {
        parse_negotiate_header(r, neg);
    }
    else { /* configure negotiation on non-transparent resource */
        neg->may_choose = 1;
    }

    maybe_add_default_accepts(neg, prefer_scripts);

    alg_result = best_match(neg, bestp);

    /* alg_result is one of
     *   alg_choice: a best variant is chosen
     *   alg_list: no best variant is chosen
     */

    if (alg_result == alg_list) {
        /* send a list response or HTTP_NOT_ACCEPTABLE error response  */

        neg->send_alternates = 1; /* always include Alternates header */
        set_neg_headers(r, neg, alg_result);
        store_variant_list(r, neg);

        if (neg->is_transparent && neg->ua_supports_trans) {
            /* XXX todo: expires? cachability? */

            /* Some HTTP/1.0 clients are known to choke when they get
             * a 300 (multiple choices) response without a Location
             * header.  However the 300 code response we are are about
             * to generate will only reach 1.0 clients which support
             * transparent negotiation, and they should be OK. The
             * response should never reach older 1.0 clients, even if
             * we have CacheNegotiatedDocs enabled, because no 1.0
             * proxy cache (we know of) will cache and return 300
             * responses (they certainly won't if they conform to the
             * HTTP/1.0 specification).
             */
            return HTTP_MULTIPLE_CHOICES;
        }

        if (!*bestp) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "no acceptable variant: %s", r->filename);
            return HTTP_NOT_ACCEPTABLE;
        }
    }

    /* Variant selection chose a variant */

    /* XXX todo: merge the two cases in the if statement below */
    if (neg->is_transparent) {

        if ((res = setup_choice_response(r, neg, *bestp)) != 0) {
            return res; /* return if error */
        }
    }
    else {
        set_neg_headers(r, neg, alg_result);
    }

    /* Make sure caching works - Vary should handle HTTP/1.1, but for
     * HTTP/1.0, we can't allow caching at all.
     */

    /* XXX: Note that we only set r->no_cache to 1, which causes
     * Expires: <now> to be added, when responding to a HTTP/1.0
     * client.  If we return the response to a 1.1 client, we do not
     * add Expires <now>, because doing so would degrade 1.1 cache
     * performance by preventing re-use of the response without prior
     * revalidation.  On the other hand, if the 1.1 client is a proxy
     * which was itself contacted by a 1.0 client, or a proxy cache
     * which can be contacted later by 1.0 clients, then we currently
     * rely on this 1.1 proxy to add the Expires: <now> when it
     * forwards the response.
     *
     * XXX: TODO: Find out if the 1.1 spec requires proxies and
     * tunnels to add Expires: <now> when forwarding the response to
     * 1.0 clients.  I (kh) recall it is rather vague on this point.
     * Testing actual 1.1 proxy implementations would also be nice. If
     * Expires: <now> is not added by proxies then we need to always
     * include Expires: <now> ourselves to ensure correct caching, but
     * this would degrade HTTP/1.1 cache efficiency unless we also add
     * Cache-Control: max-age=N, which we currently don't.
     *
     * Roy: No, we are not going to screw over HTTP future just to
     *      ensure that people who can't be bothered to upgrade their
     *      clients will always receive perfect server-side negotiation.
     *      Hell, those clients are sending bogus accept headers anyway.
     *
     *      Manual setting of cache-control/expires always overrides this
     *      automated kluge, on purpose.
     */

    if ((!do_cache_negotiated_docs(r->server)
         && (r->proto_num < HTTP_VERSION(1,1)))
         && neg->count_multiviews_variants != 1) {
        r->no_cache = 1;
    }

    return OK;
}