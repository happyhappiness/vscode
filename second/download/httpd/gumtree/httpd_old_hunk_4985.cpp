    int result;
    int nargs = 0;

    spec = create_vm_spec(&pool, r, cfg, server_cfg, prov_spec->file_name,
                          NULL, 0, prov_spec->function_name, "authz provider");

    L = ap_lua_get_lua_state(pool, spec);
    if (L == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02314)
                      "Unable to compile VM for authz provider %s", prov_spec->name);
        return AUTHZ_GENERAL_ERROR;
    }
    lua_getglobal(L, prov_spec->function_name);
    if (!lua_isfunction(L, -1)) {
        ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(02319)
                      "Unable to find function %s in %s",
                      prov_spec->function_name, prov_spec->file_name);
        return AUTHZ_GENERAL_ERROR;
    }
    ap_lua_run_lua_request(L, r);
    if (prov_spec->args) {
        int i;
        if (!lua_checkstack(L, prov_spec->args->nelts)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02315)
                          "Error: authz provider %s: too many arguments", prov_spec->name);
            return AUTHZ_GENERAL_ERROR;
        }
        for (i = 0; i < prov_spec->args->nelts; i++) {
            const char *arg = APR_ARRAY_IDX(prov_spec->args, i, const char *);
            lua_pushstring(L, arg);
        }
        nargs = prov_spec->args->nelts;
    }
    if (lua_pcall(L, 1 + nargs, 1, 0)) {
        const char *err = lua_tostring(L, -1);
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02316)
                      "Error executing authz provider %s: %s", prov_spec->name, err);
        return AUTHZ_GENERAL_ERROR;
    }
    if (!lua_isnumber(L, -1)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02317)
                      "Error: authz provider %s did not return integer", prov_spec->name);
        return AUTHZ_GENERAL_ERROR;
    }
    result = lua_tointeger(L, -1);
    switch (result) {
        case AUTHZ_DENIED:
        case AUTHZ_GRANTED:
        case AUTHZ_NEUTRAL:
        case AUTHZ_GENERAL_ERROR:
        case AUTHZ_DENIED_NO_USER:
