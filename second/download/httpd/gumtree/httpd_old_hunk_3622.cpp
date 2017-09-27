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
