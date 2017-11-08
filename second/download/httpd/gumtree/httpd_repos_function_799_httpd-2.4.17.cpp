static void modssl_ctx_cfg_merge_server(apr_pool_t *p,
                                        modssl_ctx_t *base,
                                        modssl_ctx_t *add,
                                        modssl_ctx_t *mrg)
{
    modssl_ctx_cfg_merge(p, base, add, mrg);

    /*
     * For better backwards compatibility with releases up to 2.4.7,
     * merging global and vhost-level SSLCertificateFile and
     * SSLCertificateKeyFile directives needs special treatment.
     * See also PR 56306 and 56353.
     */
    modssl_ctx_cfg_merge_certkeys_array(p, base->pks->cert_files,
                                        add->pks->cert_files,
                                        mrg->pks->cert_files);
    modssl_ctx_cfg_merge_certkeys_array(p, base->pks->key_files,
                                        add->pks->key_files,
                                        mrg->pks->key_files);

    cfgMergeString(pks->ca_name_path);
    cfgMergeString(pks->ca_name_file);

#ifdef HAVE_TLS_SESSION_TICKETS
    cfgMergeString(ticket_key->file_path);
#endif
}