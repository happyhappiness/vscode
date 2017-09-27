    apr_bucket_brigade *tmpBucket;
    lua_State *L;
    ap_lua_vm_spec *spec;
    int broken;
} lua_filter_ctx;

apr_thread_mutex_t* lua_ivm_mutex = NULL;

/**
 * error reporting if lua has an error.
 * Extracts the error from lua stack and prints
 */
static void report_lua_error(lua_State *L, request_rec *r)
{
    const char *lua_response;
    r->status = HTTP_INTERNAL_SERVER_ERROR;
    r->content_type = "text/html";
    ap_rputs("<b>Error!</b>\n", r);
    ap_rputs("<p>", r);
    lua_response = lua_tostring(L, -1);
    ap_rputs(lua_response, r);
    ap_rputs("</p>\n", r);

    ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, r->pool, APLOGNO(01471) "Lua error: %s",
                  lua_response);
}

static void lua_open_callback(lua_State *L, apr_pool_t *p, void *ctx)
