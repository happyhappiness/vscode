static request_rec *internal_internal_redirect(const char *new_uri,
                                               request_rec *r) {
    int access_status;
    request_rec *new;

    if (ap_is_recursion_limit_exceeded(r)) {
        ap_die(HTTP_INTERNAL_SERVER_ERROR, r);
        return NULL;
    }

    new = (request_rec *) apr_pcalloc(r->pool, sizeof(request_rec));

    new->connection = r->connection;
    new->server     = r->server;
    new->pool       = r->pool;

    /*
     * A whole lot of this really ought to be shared with http_protocol.c...
     * another missing cleanup.  It's particularly inappropriate to be
     * setting header_only, etc., here.
     */

    new->method          = r->method;
    new->method_number   = r->method_number;
    new->allowed_methods = ap_make_method_list(new->pool, 2);
    ap_parse_uri(new, new_uri);
    new->parsed_uri.port_str = r->parsed_uri.port_str;
    new->parsed_uri.port = r->parsed_uri.port;

    new->request_config = ap_create_request_config(r->pool);

    new->per_dir_config = r->server->lookup_defaults;

    new->prev = r;
    r->next   = new;

    /* Must have prev and next pointers set before calling create_request
     * hook.
     */
    ap_run_create_request(new);

    /* Inherit the rest of the protocol info... */

    new->the_request = r->the_request;

    new->allowed         = r->allowed;

    new->status          = r->status;
    new->assbackwards    = r->assbackwards;
    new->header_only     = r->header_only;
    new->protocol        = r->protocol;
    new->proto_num       = r->proto_num;
    new->hostname        = r->hostname;
    new->request_time    = r->request_time;
    new->main            = r->main;

    new->headers_in      = r->headers_in;
    new->headers_out     = apr_table_make(r->pool, 12);
    new->err_headers_out = r->err_headers_out;
    new->subprocess_env  = rename_original_env(r->pool, r->subprocess_env);
    new->notes           = apr_table_make(r->pool, 5);

    new->htaccess        = r->htaccess;
    new->no_cache        = r->no_cache;
    new->expecting_100   = r->expecting_100;
    new->no_local_copy   = r->no_local_copy;
    new->read_length     = r->read_length;     /* We can only read it once */
    new->vlist_validator = r->vlist_validator;

    new->proto_output_filters  = r->proto_output_filters;
    new->proto_input_filters   = r->proto_input_filters;

    new->input_filters   = new->proto_input_filters;

    if (new->main) {
        ap_filter_t *f, *nextf;

        /* If this is a subrequest, the filter chain may contain a
         * mixture of filters specific to the old request (r), and
         * some inherited from r->main.  Here, inherit that filter
         * chain, and remove all those which are specific to the old
         * request; ensuring the subreq filter is left in place. */
        new->output_filters = r->output_filters;

        f = new->output_filters;
        do {
            nextf = f->next;

            if (f->r == r && f->frec != ap_subreq_core_filter_handle) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "dropping filter '%s' in internal redirect from %s to %s",
                              f->frec->name, r->unparsed_uri, new_uri);

                /* To remove the filter, first set f->r to the *new*
                 * request_rec, so that ->output_filters on 'new' is
                 * changed (if necessary) when removing the filter. */
                f->r = new;
                ap_remove_output_filter(f);
            }

            f = nextf;

            /* Stop at the protocol filters.  If a protocol filter has
             * been newly installed for this resource, better leave it
             * in place, though it's probably a misconfiguration or
             * filter bug to get into this state. */
        } while (f && f != new->proto_output_filters);
    }
    else {
        /* If this is not a subrequest, clear out all
         * resource-specific filters. */
        new->output_filters  = new->proto_output_filters;
    }

    update_r_in_filters(new->input_filters, r, new);
    update_r_in_filters(new->output_filters, r, new);

    apr_table_setn(new->subprocess_env, "REDIRECT_STATUS",
                   apr_itoa(r->pool, r->status));

    /*
     * XXX: hmm.  This is because mod_setenvif and mod_unique_id really need
     * to do their thing on internal redirects as well.  Perhaps this is a
     * misnamed function.
     */
    if ((access_status = ap_run_post_read_request(new))) {
        ap_die(access_status, new);
        return NULL;
    }

    return new;
}