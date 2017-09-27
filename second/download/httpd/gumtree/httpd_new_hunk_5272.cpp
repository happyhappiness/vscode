    apr_bucket_brigade *tmpBucket;
    lua_State *L;
    ap_lua_vm_spec *spec;
    int broken;
} lua_filter_ctx;

apr_global_mutex_t *lua_ivm_mutex;
apr_shm_t *lua_ivm_shm;
char *lua_ivm_shmfile;

static apr_status_t shm_cleanup_wrapper(void *unused) {
    if (lua_ivm_shm) {
        return apr_shm_destroy(lua_ivm_shm);
    }
    return OK;
}

/**
 * error reporting if lua has an error.
 * Extracts the error from lua stack and prints
 */
static void report_lua_error(lua_State *L, request_rec *r)
{
    const char *lua_response;
    r->status = HTTP_INTERNAL_SERVER_ERROR;
    r->content_type = "text/html";
    ap_rputs("<h3>Error!</h3>\n", r);
    ap_rputs("<pre>", r);
    lua_response = lua_tostring(L, -1);
    ap_rputs(ap_escape_html(r->pool, lua_response), r);
    ap_rputs("</pre>\n", r);

    ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, r->pool, APLOGNO(01471) "Lua error: %s",
                  lua_response);
}

static void lua_open_callback(lua_State *L, apr_pool_t *p, void *ctx)
