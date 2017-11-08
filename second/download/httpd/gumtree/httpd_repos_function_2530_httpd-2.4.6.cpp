static apr_status_t session_crypto_encode(request_rec * r, session_rec * z)
{

    char *encoded = NULL;
    apr_status_t res;
    const apr_crypto_t *f = NULL;
    session_crypto_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
            &session_crypto_module);

    if (dconf->passphrases_set && z->encoded && *z->encoded) {
        apr_pool_userdata_get((void **)&f, CRYPTO_KEY, r->server->process->pconf);
        res = encrypt_string(r, f, dconf, z->encoded, &encoded);
        if (res != OK) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01841)
                    "encrypt session failed");
            return res;
        }
        z->encoded = encoded;
    }

    return OK;

}