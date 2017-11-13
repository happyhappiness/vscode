ap_log_error(APLOG_MARK, APLOG_ERR, rs, s,
            "mod_lua: Failed to create shared memory segment on file %s",
                     lua_ivm_shmfile);