static void modssl_ctx_cfg_merge_server(apr_pool_t *p,
                                        modssl_ctx_t *base,
                                        modssl_ctx_t *add,
                                        modssl_ctx_t *mrg)
{
    modssl_ctx_cfg_merge(p, base, add, mrg);

    cfgMergeArray(pks->cert_files);
    cfgMergeArray(pks->key_files);

    cfgMergeString(pks->ca_name_path);
    cfgMergeString(pks->ca_name_file);

#ifdef HAVE_TLS_SESSION_TICKETS
    cfgMergeString(ticket_key->file_path);
#endif
}