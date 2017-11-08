static int dbd_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                           apr_pool_t *ptemp, server_rec *s)
{
    svr_cfg *svr;
    server_rec *sp;
    for (sp = s; sp; sp = sp->next) {
        svr = ap_get_module_config(sp->module_config, &dbd_module);
        svr->prepared = apr_hash_get(dbd_prepared_defns, sp->server_hostname,
                                     APR_HASH_KEY_STRING);
    }
    return OK;
}