static apr_status_t expires_filter(ap_filter_t *f,
                                   apr_bucket_brigade *b)
{
    request_rec *r;
    expires_dir_config *conf;
    const char *expiry;
    apr_table_t *t;

    r = f->r;
    conf = (expires_dir_config *) ap_get_module_config(r->per_dir_config,
                                                       &expires_module);

    /*
     * Check to see which output header table we should use;
     * mod_cgi loads script fields into r->err_headers_out,
     * for instance.
     */
    expiry = apr_table_get(r->err_headers_out, "Expires");
    if (expiry != NULL) {
        t = r->err_headers_out;
    }
    else {
        expiry = apr_table_get(r->headers_out, "Expires");
        t = r->headers_out;
    }
    if (expiry == NULL) {
        /*
         * No expiration has been set, so we can apply any managed by
         * this module.  First, check to see if there is an applicable
         * ExpiresByType directive.
         */
        expiry = apr_table_get(conf->expiresbytype, 
                               ap_field_noparam(r->pool, r->content_type));
        if (expiry == NULL) {
            int usedefault = 1;
            /*
             * See if we have a wildcard entry for the major type.
             */
            if (conf->wildcards) {
                char *checkmime;
                char *spos;
                checkmime = apr_pstrdup(r->pool, r->content_type);
                spos = checkmime ? ap_strchr(checkmime, '/') : NULL;
                if (spos != NULL) {
                    /*
                     * Without a '/' character, nothing we have will match.
                     * However, we have one.
                     */
                    if (strlen(++spos) > 0) {
                        *spos++ = '*';
                        *spos = '\0';
                    }
                    else {
                        checkmime = apr_pstrcat(r->pool, checkmime, "*", NULL);
                    }
                    expiry = apr_table_get(conf->expiresbytype, checkmime);
                    usedefault = (expiry == NULL);
                }
            }
            if (usedefault) {
                /*
                 * Use the ExpiresDefault directive
                 */
                expiry = conf->expiresdefault;
            }
        }
        if (expiry != NULL) {
            set_expiration_fields(r, expiry, t);
        }
    }
    ap_remove_output_filter(f);
    return ap_pass_brigade(f->next, b);
}