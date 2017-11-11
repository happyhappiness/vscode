static const char *add_ct_output_filters(cmd_parms *cmd, void *conf_,
                                         const char *arg, const char *arg2)
{
    core_dir_config *conf = conf_;
    ap_filter_rec_t *old, *new = NULL;
    const char *filter_name;

    if (!conf->ct_output_filters) {
        conf->ct_output_filters = apr_hash_make(cmd->pool);
        old = NULL;
    }
    else {
        old = (ap_filter_rec_t*) apr_hash_get(conf->ct_output_filters, arg2,
                                              APR_HASH_KEY_STRING);
    }

    while (*arg &&
           (filter_name = ap_getword(cmd->pool, &arg, ';')) &&
           strcmp(filter_name, "")) {
        new = apr_pcalloc(cmd->pool, sizeof(ap_filter_rec_t));
        new->name = filter_name;

        /* We found something, so let's append it.  */
        if (old) {
            new->next = old;
        }
        old = new;
    }

    if (!new) {
        return "invalid filter name";
    }
    
    apr_hash_set(conf->ct_output_filters, arg2, APR_HASH_KEY_STRING, new);

    return NULL;
}