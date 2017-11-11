static void modssl_ctx_cfg_merge_proxy(modssl_ctx_t *base,
                                       modssl_ctx_t *add,
                                       modssl_ctx_t *mrg)
{
    modssl_ctx_cfg_merge(base, add, mrg);

    cfgMergeString(pkp->cert_file);
    cfgMergeString(pkp->cert_path);
}