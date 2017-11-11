static dav_error *dav_get_resource(request_rec *r, int label_allowed,
                                   int use_checked_in, dav_resource **res_p)
{
    dav_dir_conf *conf;
    const char *label = NULL;
    dav_error *err;

    /* if the request target can be overridden, get any target selector */
    if (label_allowed) {
        label = apr_table_get(r->headers_in, "label");
    }

    conf = ap_get_module_config(r->per_dir_config, &dav_module);
    /* assert: conf->provider != NULL */

    /* resolve the resource */
    err = (*conf->provider->repos->get_resource)(r, conf->dir,
                                                 label, use_checked_in,
                                                 res_p);
    if (err != NULL) {
        err = dav_push_error(r->pool, err->status, 0,
                             "Could not fetch resource information.", err);
        return err;
    }

    /* Note: this shouldn't happen, but just be sure... */
    if (*res_p == NULL) {
        /* ### maybe use HTTP_INTERNAL_SERVER_ERROR */
        return dav_new_error(r->pool, HTTP_NOT_FOUND, 0, 0,
                             apr_psprintf(r->pool,
                                          "The provider did not define a "
                                          "resource for %s.",
                                          ap_escape_html(r->pool, r->uri)));
    }

    /* ### hmm. this doesn't feel like the right place or thing to do */
    /* if there were any input headers requiring a Vary header in the response,
     * add it now */
    dav_add_vary_header(r, r, *res_p);

    return NULL;
}