            }
            proxy_func = "H2C";
            break;
        default:
            return DECLINED;
    }
    
    ctx = apr_pcalloc(r->pool, sizeof(*ctx));
    ctx->owner      = r->connection;
    ctx->pool       = r->pool;
    ctx->rbase      = r;
    ctx->server     = r->server;
    ctx->proxy_func = proxy_func;
    ctx->is_ssl     = is_ssl;
    ctx->worker     = worker;
    ctx->conf       = conf;
    ctx->flushall   = apr_table_get(r->subprocess_env, "proxy-flushall")? 1 : 0;
    ctx->r_status   = HTTP_SERVICE_UNAVAILABLE;
    
    h2_proxy_fifo_set_create(&ctx->requests, ctx->pool, 100);
    
    ap_set_module_config(ctx->owner->conn_config, &proxy_http2_module, ctx);

    /* scheme says, this is for us. */
    apr_table_setn(ctx->rbase->notes, H2_PROXY_REQ_URL_NOTE, url);
    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, ctx->rbase, 
                  "H2: serving URL %s", url);
