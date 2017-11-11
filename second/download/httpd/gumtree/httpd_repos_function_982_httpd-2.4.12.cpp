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
        else { 
            /* We've got a willing lua filter, setup and check for a prefix */
            size_t olen;
            apr_bucket *pbktOut;
            const char* output = lua_tolstring(ctx->L, 1, &olen);

            f->ctx = ctx;
            ctx->tmpBucket = apr_brigade_create(r->pool, c->bucket_alloc);

            if (olen > 0) { 
                pbktOut = apr_bucket_heap_create(output, olen, NULL, c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(ctx->tmpBucket, pbktOut);
                rv = ap_pass_brigade(f->next, ctx->tmpBucket);
                apr_brigade_cleanup(ctx->tmpBucket);
                if (rv != APR_SUCCESS) {
                    return rv;
                }
            }
        }
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
                if (olen > 0) { 
                    pbktOut = apr_bucket_heap_create(output, olen, NULL,
                                            c->bucket_alloc);
                    APR_BRIGADE_INSERT_TAIL(ctx->tmpBucket, pbktOut);
                    rv = ap_pass_brigade(f->next, ctx->tmpBucket);
                    apr_brigade_cleanup(ctx->tmpBucket);
                    if (rv != APR_SUCCESS) {
                        return rv;
                    }
                }
            }
            else {
                ctx->broken = 1;
                ap_lua_release_state(L, ctx->spec, r);
                ap_remove_output_filter(f);
                apr_brigade_cleanup(pbbIn);
                apr_brigade_cleanup(ctx->tmpBucket);
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02663)
                              "lua: Error while executing filter: %s",
                              lua_tostring(L, -1));
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
                if (olen > 0) { 
                    pbktOut = apr_bucket_heap_create(output, olen, NULL,
                            c->bucket_alloc);
                    APR_BRIGADE_INSERT_TAIL(ctx->tmpBucket, pbktOut);
                }
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