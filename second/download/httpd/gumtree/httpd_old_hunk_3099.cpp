/**
 * Crypto decoding for the session.
 *
 * @param r The request pointer.
 * @param z A pointer to where the session will be written.
 */
AP_DECLARE(int) ap_session_crypto_decode(request_rec * r, session_rec * z)
{

    char *encoded = NULL;
    apr_status_t res;
    const apr_crypto_driver_t *driver = NULL;
    session_crypto_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
            &session_crypto_module);

    if ((dconf->passphrase_set) && z->encoded && *z->encoded) {
        apr_pool_userdata_get((void **)&driver, DRIVER_KEY, r->server->process->pconf);
        res = decrypt_string(r, driver, dconf, z->encoded, &encoded);
        if (res != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, LOG_PREFIX
                    "decrypt session failed, wrong passphrase?");
            return res;
        }
        z->encoded = encoded;
    }

