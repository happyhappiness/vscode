      
      if(L==NULL) {
        ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, lifecycle_pool, APLOGNO(01483)
                      "creating lua_State with file %s", spec->file);
        /* not available, so create */
        
        if(!vm_construct((void **)&L, spec, lifecycle_pool)) {
          apr_pool_userdata_set(L, 
                                spec->file, 
                                cleanup_lua,
                                lifecycle_pool);
        }
      }
