static void modssl_ctx_cfg_merge(modssl_ctx_t *base,
                                 modssl_ctx_t *add,
                                 modssl_ctx_t *mrg)
{
    cfgMerge(protocol, SSL_PROTOCOL_ALL);

    cfgMerge(pphrase_dialog_type, SSL_PPTYPE_UNSET);
    cfgMergeString(pphrase_dialog_path);

    cfgMergeString(cert_chain);

    cfgMerge(crl_path, NULL);
    cfgMerge(crl_file, NULL);

    cfgMergeString(auth.ca_cert_path);
    cfgMergeString(auth.ca_cert_file);
    cfgMergeString(auth.cipher_suite);
    cfgMergeInt(auth.verify_depth);
    cfgMerge(auth.verify_mode, SSL_CVERIFY_UNSET);
}