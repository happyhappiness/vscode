static int lua_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                             apr_pool_t *ptemp, server_rec *s)
{
    apr_pool_t **pool;
    const char *tempdir;
    apr_status_t rs;

    lua_ssl_val = APR_RETRIEVE_OPTIONAL_FN(ssl_var_lookup);
    lua_ssl_is_https = APR_RETRIEVE_OPTIONAL_FN(ssl_is_https);
    
    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG)
        return OK;

    /* Create ivm mutex */
    rs = ap_global_mutex_create(&lua_ivm_mutex, NULL, "lua-ivm-shm", NULL,
                            s, pconf, 0);
    if (APR_SUCCESS != rs) {
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* Create shared memory space */
    rs = apr_temp_dir_get(&tempdir, pconf);
    if (rs != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rs, s,
                 "mod_lua IVM: Failed to find temporary directory");
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    lua_ivm_shmfile = apr_psprintf(pconf, "%s/httpd_lua_shm.%ld", tempdir,
                           (long int)getpid());
    rs = apr_shm_create(&lua_ivm_shm, sizeof(apr_pool_t**),
                    (const char *) lua_ivm_shmfile, pconf);
    if (rs != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rs, s,
            "mod_lua: Failed to create shared memory segment on file %s",
                     lua_ivm_shmfile);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    pool = (apr_pool_t **)apr_shm_baseaddr_get(lua_ivm_shm);
    apr_pool_create(pool, pconf);
    apr_pool_cleanup_register(pconf, NULL, shm_cleanup_wrapper,
                          apr_pool_cleanup_null);
    return OK;
}