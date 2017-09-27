    lua_setfield(L, LUA_REGISTRYINDEX, "Apache2.Wombat.pool");
    *vm = L;

    return APR_SUCCESS;
}

/**
 * Function used to create a lua_State instance bound into the web
 * server in the appropriate scope.
 */
AP_LUA_DECLARE(lua_State*)ap_lua_get_lua_state(apr_pool_t *lifecycle_pool,
                                               ap_lua_vm_spec *spec)
{
    lua_State *L = NULL;

    if (apr_pool_userdata_get((void **)&L, spec->file,
                              lifecycle_pool) == APR_SUCCESS) {
      
      if(L==NULL) {
        ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, lifecycle_pool, APLOGNO(01483)
                      "creating lua_State with file %s", spec->file);
        /* not available, so create */
        
        if(!vm_construct(&L, spec, lifecycle_pool)) {
          AP_DEBUG_ASSERT(L != NULL);
          apr_pool_userdata_set(L, 
                                spec->file, 
                                cleanup_lua,
                                lifecycle_pool);
        }
      }
    }
        /*}*/

    return L;
}
