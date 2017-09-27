        pool = r->connection->pool;
        break;
#if APR_HAS_THREADS
    case AP_LUA_SCOPE_THREAD:
        pool = apr_thread_pool_get(r->connection->current_thread);
        break;
#endif
    default:
        ap_assert(0);
    }

    *lifecycle_pool = pool;
    return spec;
}


/**
 * "main"
 */
static int lua_handler(request_rec *r)
{
    if (strcmp(r->handler, "lua-script")) {
        return DECLINED;
    }
    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(01472)
                  "handling [%s] in mod_lua", r->filename);

    /* XXX: This seems wrong because it may generate wrong headers for HEAD requests */
    if (!r->header_only) {
        lua_State *L;
        apr_pool_t *pool;
        const ap_lua_dir_cfg *cfg = ap_get_module_config(r->per_dir_config,
                                                         &lua_module);
        ap_lua_vm_spec *spec = create_vm_spec(&pool, r, cfg, NULL, NULL, NULL,
                                              0, "handle", "request handler");

        L = ap_lua_get_lua_state(pool, spec);
        if (!L) {
            /* TODO annotate spec with failure reason */
            r->status = HTTP_INTERNAL_SERVER_ERROR;
            ap_rputs("Unable to compile VM, see logs", r);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, APLOGNO(01474) "got a vm!");
        lua_getglobal(L, "handle");
        if (!lua_isfunction(L, -1)) {
            ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01475)
                          "lua: Unable to find function %s in %s",
                          "handle",
                          spec->file);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        ap_lua_run_lua_request(L, r);
        if (lua_pcall(L, 1, 0, 0)) {
            report_lua_error(L, r);
        }
    }
    return OK;
}



/* ---------------- Configury stuff --------------- */

/** harnesses for magic hooks **/

static int lua_request_rec_hook_harness(request_rec *r, const char *name, int apr_hook_when)
