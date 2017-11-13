lua_State *ap_lua_get_lua_state(apr_pool_t *lifecycle_pool,
                                               ap_lua_vm_spec *spec, request_rec* r)
{
    lua_State *L = NULL;
    ap_lua_finfo *cache_info = NULL;
    int tryCache = 0;
    
    if (spec->scope == AP_LUA_SCOPE_SERVER) {
        char *hash;
        apr_reslist_t* reslist = NULL;
        ap_lua_server_spec* sspec = NULL;
        hash = apr_psprintf(r->pool, "reslist:%s", spec->file);
#if APR_HAS_THREADS
        apr_thread_mutex_lock(ap_lua_mutex);
#endif
        if (apr_pool_userdata_get((void **)&reslist, hash,
                                  r->server->process->pool) == APR_SUCCESS) {
            if (reslist != NULL) {
                if (apr_reslist_acquire(reslist, (void**) &sspec) == APR_SUCCESS) {
                    L = sspec->L;
                    cache_info = sspec->finfo;
                }
            }
        }
        if (L == NULL) {
            ap_lua_vm_spec* server_spec = copy_vm_spec(r->server->process->pool, spec);
            if (
                    apr_reslist_create(&reslist, spec->vm_min, spec->vm_max, spec->vm_max, 0, 
                                (apr_reslist_constructor) server_vm_construct, 
                                (apr_reslist_destructor) server_cleanup_lua, 
                                server_spec, r->server->process->pool)
                    == APR_SUCCESS && reslist != NULL) {
                apr_pool_userdata_set(reslist, hash, NULL,
                                            r->server->process->pool);
                if (apr_reslist_acquire(reslist, (void**) &sspec) == APR_SUCCESS) {
                    L = sspec->L;
                    cache_info = sspec->finfo;
                }
                else {
                    return NULL;
                }
            }
        }
#if APR_HAS_THREADS
        apr_thread_mutex_unlock(ap_lua_mutex);
#endif
    }
    else {
        if (apr_pool_userdata_get((void **)&L, spec->file,
                              lifecycle_pool) != APR_SUCCESS) {
            L = NULL;
        }
    }
    if (L == NULL) {
        ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, lifecycle_pool, APLOGNO(01483)
                        "creating lua_State with file %s", spec->file);
        /* not available, so create */

        if (!vm_construct(&L, spec, lifecycle_pool)) {
            AP_DEBUG_ASSERT(L != NULL);
            apr_pool_userdata_set(L, spec->file, cleanup_lua, lifecycle_pool);
        }
    }

    if (spec->codecache == AP_LUA_CACHE_FOREVER || (spec->bytecode && spec->bytecode_len > 0)) {
        tryCache = 1;
    }
    else {
        char* mkey;
        if (spec->scope != AP_LUA_SCOPE_SERVER) {
            mkey = apr_psprintf(r->pool, "ap_lua_modified:%s", spec->file);
            apr_pool_userdata_get((void **)&cache_info, mkey, lifecycle_pool);
            if (cache_info == NULL) {
                cache_info = apr_pcalloc(lifecycle_pool, sizeof(ap_lua_finfo));
                apr_pool_userdata_set((void*) cache_info, mkey, NULL, lifecycle_pool);
            }
        }
        if (spec->codecache == AP_LUA_CACHE_STAT) {
            apr_finfo_t lua_finfo;
            apr_stat(&lua_finfo, spec->file, APR_FINFO_MTIME|APR_FINFO_SIZE, lifecycle_pool);

            /* On first visit, modified will be zero, but that's fine - The file is 
            loaded in the vm_construct function.
            */
            if ((cache_info->modified == lua_finfo.mtime && cache_info->size == lua_finfo.size)
                    || cache_info->modified == 0) {
                tryCache = 1;
            }
            cache_info->modified = lua_finfo.mtime;
            cache_info->size = lua_finfo.size;
        }
        else if (spec->codecache == AP_LUA_CACHE_NEVER) {
            if (cache_info->runs == 0)
                tryCache = 1;
        }
        cache_info->runs++;
    }
    if (tryCache == 0 && spec->scope != AP_LUA_SCOPE_ONCE) {
        int rc;
        ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, lifecycle_pool, APLOGNO(02332)
            "(re)loading lua file %s", spec->file);
        rc = luaL_loadfile(L, spec->file);
        if (rc != 0) {
            ap_log_perror(APLOG_MARK, APLOG_ERR, 0, lifecycle_pool, APLOGNO(02333)
                          "Error loading %s: %s", spec->file,
                          rc == LUA_ERRMEM ? "memory allocation error"
                                           : lua_tostring(L, 0));
            return 0;
        }
        lua_pcall(L, 0, LUA_MULTRET, 0);
    }

    return L;
}