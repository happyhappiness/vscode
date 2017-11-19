static int session_crypto_init(apr_pool_t *p, apr_pool_t *plog,
        apr_pool_t *ptemp, server_rec *s)
{
    const apr_crypto_driver_t *driver = NULL;
    apr_crypto_t *f = NULL;

    session_crypto_conf *conf = ap_get_module_config(s->module_config,
            &session_crypto_module);

    /* session_crypto_init() will be called twice. Don't bother
     * going through all of the initialization on the first call
     * because it will just be thrown away.*/
    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG) {
        return OK;
    }

    if (conf->library) {

        const apu_err_t *err = NULL;
        apr_status_t rv;

        rv = apr_crypto_init(p);
        if (APR_SUCCESS != rv) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(01843)
                    "APR crypto could not be initialised");
            return rv;
        }

        rv = apr_crypto_get_driver(&driver, conf->library, conf->params, &err, p);
        if (APR_EREINIT == rv) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s, APLOGNO(01844)
                    "warning: crypto for '%s' was already initialised, "
                    "using existing configuration", conf->library);
            rv = APR_SUCCESS;
        }
        if (APR_SUCCESS != rv && err) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(01845)
                    "%s", err->msg);
            return rv;
        }
        if (APR_ENOTIMPL == rv) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(01846)
                    "The crypto library '%s' could not be found",
                    conf->library);
            return rv;
        }
        if (APR_SUCCESS != rv || !driver) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(01847)
                    "The crypto library '%s' could not be loaded",
                    conf->library);
            return rv;
        }

        rv = apr_crypto_make(&f, driver, conf->params, p);
        if (APR_SUCCESS != rv) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(01848)
                    "The crypto library '%s' could not be initialised",
                    conf->library);
            return rv;
        }

        ap_log_error(APLOG_MARK, APLOG_INFO, rv, s, APLOGNO(01849)
                "The crypto library '%s' was loaded successfully",
                conf->library);

        apr_pool_userdata_set((const void *)f, CRYPTO_KEY,
                apr_pool_cleanup_null, s->process->pconf);

    }

    return OK;
}