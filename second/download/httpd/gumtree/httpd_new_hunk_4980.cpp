        pool = r->connection->pool;
        break;
#if APR_HAS_THREADS
    case AP_LUA_SCOPE_THREAD:
        pool = apr_thread_pool_get(r->connection->current_thread);
        break;
    case AP_LUA_SCOPE_SERVER:
        pool = r->server->process->pool;
        break;
#endif
    default:
        ap_assert(0);
    }

    *lifecycle_pool = pool;
    return spec;
}

static const char* ap_lua_interpolate_string(apr_pool_t* pool, const char* string, const char** values)
{
    char *stringBetween;
    const char* ret;
    int srclen,x,y;
    srclen = strlen(string);
    ret = "";
    y = 0;
    for (x=0; x < srclen; x++) {
        if (string[x] == '$' && x != srclen-1 && string[x+1] >= '0' && string[x+1] <= '9') {
            int v = *(string+x+1) - '0';
            if (x-y > 0) {
                stringBetween = apr_pstrndup(pool, string+y, x-y);
            }
            else {
                stringBetween = "";
            }
            ret = apr_pstrcat(pool, ret, stringBetween, values[v], NULL);
            y = ++x+1;
        }
    }
    
    if (x-y > 0 && y > 0) {
        stringBetween = apr_pstrndup(pool, string+y, x-y);
        ret = apr_pstrcat(pool, ret, stringBetween, NULL);
    }
    /* If no replacement was made, just return the original string */
    else if (y == 0) {
        return string;
    }
    return ret;
}



/**
 * "main"
 */
static int lua_handler(request_rec *r)
{
    int rc = OK;
    if (strcmp(r->handler, "lua-script")) {
        return DECLINED;
    }
    /* Decline the request if the script does not exist (or is a directory),
     * rather than just returning internal server error */
    if (
            (r->finfo.filetype == APR_NOFILE)
            || (r->finfo.filetype & APR_DIR)
        ) {
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

        L = ap_lua_get_lua_state(pool, spec, r);
        if (!L) {
            /* TODO annotate spec with failure reason */
            r->status = HTTP_INTERNAL_SERVER_ERROR;
            ap_rputs("Unable to compile VM, see logs", r);
            ap_lua_release_state(L, spec, r);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, APLOGNO(01474) "got a vm!");
        lua_getglobal(L, "handle");
        if (!lua_isfunction(L, -1)) {
            ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01475)
                          "lua: Unable to find function %s in %s",
                          "handle",
                          spec->file);
            ap_lua_release_state(L, spec, r);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        ap_lua_run_lua_request(L, r);
        if (lua_pcall(L, 1, 1, 0)) {
            report_lua_error(L, r);
        }
        if (lua_isnumber(L, -1)) {
            rc = lua_tointeger(L, -1);
        }
        ap_lua_release_state(L, spec, r);
    }
    return rc;
}


/* ------------------- Input/output content filters ------------------- */


static apr_status_t lua_setup_filter_ctx(ap_filter_t* f, request_rec* r, lua_filter_ctx** c) {
    apr_pool_t *pool;
    ap_lua_vm_spec *spec;
    int n, rc;
    lua_State *L;
    lua_filter_ctx *ctx;    
    ap_lua_server_cfg *server_cfg = ap_get_module_config(r->server->module_config,
                                                        &lua_module);
    const ap_lua_dir_cfg *cfg = ap_get_module_config(r->per_dir_config,
                                                    &lua_module);
    
    ctx = apr_pcalloc(r->pool, sizeof(lua_filter_ctx));
    ctx->broken = 0;
    *c = ctx;
    /* Find the filter that was called */
    for (n = 0; n < cfg->mapped_filters->nelts; n++) {
        ap_lua_filter_handler_spec *hook_spec =
            ((ap_lua_filter_handler_spec **) cfg->mapped_filters->elts)[n];

        if (hook_spec == NULL) {
            continue;
        }
        if (!strcasecmp(hook_spec->filter_name, f->frec->name)) {
            spec = create_vm_spec(&pool, r, cfg, server_cfg,
                                    hook_spec->file_name,
                                    NULL,
                                    0,
                                    hook_spec->function_name,
                                    "filter");
            L = ap_lua_get_lua_state(pool, spec, r);
            if (L) {
                L = lua_newthread(L);
            }

            if (!L) {
                ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(02328)
                                "lua: Failed to obtain lua interpreter for %s %s",
                                hook_spec->function_name, hook_spec->file_name);
                ap_lua_release_state(L, spec, r);
                return APR_EGENERAL;
            }
            if (hook_spec->function_name != NULL) {
                lua_getglobal(L, hook_spec->function_name);
                if (!lua_isfunction(L, -1)) {
                    ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(02329)
                                    "lua: Unable to find function %s in %s",
                                    hook_spec->function_name,
                                    hook_spec->file_name);
                    ap_lua_release_state(L, spec, r);
                    return APR_EGENERAL;
                }

                ap_lua_run_lua_request(L, r);
            }
            else {
                int t;
                ap_lua_run_lua_request(L, r);

                t = lua_gettop(L);
                lua_setglobal(L, "r");
                lua_settop(L, t);
            }
            ctx->L = L;
            ctx->spec = spec;
            
            /* If a Lua filter is interested in filtering a request, it must first do a yield, 
             * otherwise we'll assume that it's not interested and pretend we didn't find it.
             */
            rc = lua_resume(L, 1);
            if (rc == LUA_YIELD) {
                return OK;
            }
            else {
                ap_lua_release_state(L, spec, r);
                return APR_ENOENT;
            }
        }
    }
    return APR_ENOENT;
}

static apr_status_t lua_output_filter_handle(ap_filter_t *f, apr_bucket_brigade *pbbIn) {
    request_rec *r = f->r;
    int rc;
    lua_State *L;
    lua_filter_ctx* ctx;
    conn_rec *c = r->connection;
    apr_bucket *pbktIn;
    apr_status_t rv;
    
    /* Set up the initial filter context and acquire the function.
     * The corresponding Lua function should yield here.
     */
    if (!f->ctx) {
        rc = lua_setup_filter_ctx(f,r,&ctx);
        if (rc == APR_EGENERAL) {
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        if (rc == APR_ENOENT) {
            /* No filter entry found (or the script declined to filter), just pass on the buckets */
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next,pbbIn);
        }
        f->ctx = ctx;
        ctx->tmpBucket = apr_brigade_create(r->pool, c->bucket_alloc);
    }
    ctx = (lua_filter_ctx*) f->ctx;
    L = ctx->L;
    /* While the Lua function is still yielding, pass in buckets to the coroutine */
    if (!ctx->broken) {
        for (pbktIn = APR_BRIGADE_FIRST(pbbIn);
            pbktIn != APR_BRIGADE_SENTINEL(pbbIn);
            pbktIn = APR_BUCKET_NEXT(pbktIn))
            {
            const char *data;
            apr_size_t len;
            apr_bucket *pbktOut;

            /* read the bucket */
            apr_bucket_read(pbktIn,&data,&len,APR_BLOCK_READ);

            /* Push the bucket onto the Lua stack as a global var */
            lua_pushlstring(L, data, len);
            lua_setglobal(L, "bucket");
            
            /* If Lua yielded, it means we have something to pass on */
            if (lua_resume(L, 0) == LUA_YIELD) {
                size_t olen;
                const char* output = lua_tolstring(L, 1, &olen);
                pbktOut = apr_bucket_heap_create(output, olen, NULL,
                                        c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(ctx->tmpBucket, pbktOut);
                rv = ap_pass_brigade(f->next, ctx->tmpBucket);
                apr_brigade_cleanup(ctx->tmpBucket);
                if (rv != APR_SUCCESS) {
                    return rv;
                }
            }
            else {
                ctx->broken = 1;
                ap_lua_release_state(L, ctx->spec, r);
                ap_remove_output_filter(f);
                apr_brigade_cleanup(pbbIn);
                apr_brigade_cleanup(ctx->tmpBucket);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
        }
        /* If we've safely reached the end, do a final call to Lua to allow for any 
        finishing moves by the script, such as appending a tail. */
        if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(pbbIn))) {
            apr_bucket *pbktEOS;
            lua_pushnil(L);
            lua_setglobal(L, "bucket");
            if (lua_resume(L, 0) == LUA_YIELD) {
                apr_bucket *pbktOut;
                size_t olen;
                const char* output = lua_tolstring(L, 1, &olen);
                pbktOut = apr_bucket_heap_create(output, olen, NULL,
                                        c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(ctx->tmpBucket, pbktOut);
            }
            pbktEOS = apr_bucket_eos_create(c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(ctx->tmpBucket, pbktEOS);
            ap_lua_release_state(L, ctx->spec, r);
            rv = ap_pass_brigade(f->next, ctx->tmpBucket);
            apr_brigade_cleanup(ctx->tmpBucket);
            if (rv != APR_SUCCESS) {
                return rv;
            }
        }
    }
    /* Clean up */
    apr_brigade_cleanup(pbbIn);
    return APR_SUCCESS;    
}



static apr_status_t lua_input_filter_handle(ap_filter_t *f,
                                       apr_bucket_brigade *pbbOut,
                                       ap_input_mode_t eMode,
                                       apr_read_type_e eBlock,
                                       apr_off_t nBytes) 
{
    request_rec *r = f->r;
    int rc, lastCall = 0;
    lua_State *L;
    lua_filter_ctx* ctx;
    conn_rec *c = r->connection;
    apr_status_t ret;
    
    /* Set up the initial filter context and acquire the function.
     * The corresponding Lua function should yield here.
     */
    if (!f->ctx) {
        rc = lua_setup_filter_ctx(f,r,&ctx);
        f->ctx = ctx;
        if (rc == APR_EGENERAL) {
            ctx->broken = 1;
            ap_remove_input_filter(f); 
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        if (rc == APR_ENOENT ) {
            ap_remove_input_filter(f);
            ctx->broken = 1;
        }
        if (rc == APR_SUCCESS) {
            ctx->tmpBucket = apr_brigade_create(r->pool, c->bucket_alloc);
        }
    }
    ctx = (lua_filter_ctx*) f->ctx;
    L = ctx->L;
    /* If the Lua script broke or denied serving the request, just pass the buckets through */
    if (ctx->broken) {
        return ap_get_brigade(f->next, pbbOut, eMode, eBlock, nBytes);
    }
    
    if (APR_BRIGADE_EMPTY(ctx->tmpBucket)) {
        ret = ap_get_brigade(f->next, ctx->tmpBucket, eMode, eBlock, nBytes);
        if (eMode == AP_MODE_EATCRLF || ret != APR_SUCCESS)
            return ret;
    }
    
    /* While the Lua function is still yielding, pass buckets to the coroutine */
    if (!ctx->broken) {
        lastCall = 0;
        while(!APR_BRIGADE_EMPTY(ctx->tmpBucket)) {
            apr_bucket *pbktIn = APR_BRIGADE_FIRST(ctx->tmpBucket);
            apr_bucket *pbktOut;
            const char *data;
            apr_size_t len;
            
            if (APR_BUCKET_IS_EOS(pbktIn)) {
                APR_BUCKET_REMOVE(pbktIn);
                break;
            }

            /* read the bucket */
            ret = apr_bucket_read(pbktIn, &data, &len, eBlock);
            if (ret != APR_SUCCESS)
                return ret;

            /* Push the bucket onto the Lua stack as a global var */
            lastCall++;
            lua_pushlstring(L, data, len);
            lua_setglobal(L, "bucket");
            
            /* If Lua yielded, it means we have something to pass on */
            if (lua_resume(L, 0) == LUA_YIELD) {
                size_t olen;
                const char* output = lua_tolstring(L, 1, &olen);
                pbktOut = apr_bucket_heap_create(output, olen, 0, c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(pbbOut, pbktOut);
                apr_bucket_delete(pbktIn);
                return APR_SUCCESS;
            }
            else {
                ctx->broken = 1;
                ap_lua_release_state(L, ctx->spec, r);
                ap_remove_input_filter(f); 
                apr_bucket_delete(pbktIn);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
        }
        /* If we've safely reached the end, do a final call to Lua to allow for any 
        finishing moves by the script, such as appending a tail. */
        if (lastCall == 0) {
            apr_bucket *pbktEOS = apr_bucket_eos_create(c->bucket_alloc);
            lua_pushnil(L);
            lua_setglobal(L, "bucket");
            if (lua_resume(L, 0) == LUA_YIELD) {
                apr_bucket *pbktOut;
                size_t olen;
                const char* output = lua_tolstring(L, 1, &olen);
                pbktOut = apr_bucket_heap_create(output, olen, 0, c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(pbbOut, pbktOut);
            }
            APR_BRIGADE_INSERT_TAIL(pbbOut,pbktEOS);
            ap_lua_release_state(L, ctx->spec, r);
        }
    }
    return APR_SUCCESS;
}


/* ---------------- Configury stuff --------------- */

/** harnesses for magic hooks **/

static int lua_request_rec_hook_harness(request_rec *r, const char *name, int apr_hook_when)
