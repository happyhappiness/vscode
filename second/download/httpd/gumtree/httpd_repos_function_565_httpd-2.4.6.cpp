static void *merge_ident_dir_config(apr_pool_t *p, void *old_, void *new_)
{
    ident_config_rec *conf = (ident_config_rec *)apr_pcalloc(p, sizeof(*conf));
    ident_config_rec *old = (ident_config_rec *) old_;
    ident_config_rec *new = (ident_config_rec *) new_;

    conf->timeout = new->timeout_unset
                        ? old->timeout
                        : new->timeout;

    conf->do_rfc1413 = new->do_rfc1413 & RFC1413_UNSET
                           ? old->do_rfc1413
                           : new->do_rfc1413;

    return (void *)conf;
}