static void expires_insert_filter(request_rec *r)
{
    expires_dir_config *conf;

    /* Don't add Expires headers to errors */
    if (ap_is_HTTP_ERROR(r->status)) {
        return;
    }
    /* Say no to subrequests */
    if (r->main != NULL) {
        return;
    }
    conf = (expires_dir_config *) ap_get_module_config(r->per_dir_config,
                                                       &expires_module);

    /* Check to see if the filter is enabled and if there are any applicable 
     * config directives for this directory scope
     */
    if (conf->active != ACTIVE_ON ||
        (apr_is_empty_table(conf->expiresbytype) && !conf->expiresdefault)) {
        return;
    }
    ap_add_output_filter("MOD_EXPIRES", NULL, r, r->connection);
    return;
}