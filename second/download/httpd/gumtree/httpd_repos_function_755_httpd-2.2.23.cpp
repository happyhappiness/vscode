static void modssl_ctx_cfg_merge_server(modssl_ctx_t *base,
                                        modssl_ctx_t *add,
                                        modssl_ctx_t *mrg)
{
    int i;

    modssl_ctx_cfg_merge(base, add, mrg);

    for (i = 0; i < SSL_AIDX_MAX; i++) {
        cfgMergeString(pks->cert_files[i]);
        cfgMergeString(pks->key_files[i]);
    }

    cfgMergeString(pks->ca_name_path);
    cfgMergeString(pks->ca_name_file);
}