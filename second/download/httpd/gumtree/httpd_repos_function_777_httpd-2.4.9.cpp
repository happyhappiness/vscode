static void modssl_ctx_cfg_merge_proxy(apr_pool_t *p,
                                       modssl_ctx_t *base,
                                       modssl_ctx_t *add,
                                       modssl_ctx_t *mrg)
{
    modssl_ctx_cfg_merge(p, base, add, mrg);

    cfgMergeString(pkp->cert_file);
    cfgMergeString(pkp->cert_path);
    cfgMergeString(pkp->ca_cert_file);
}