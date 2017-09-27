                      c->id, engine_type);
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, 
                      "H2: hosting engine %s", ctx->engine_id);
    }
    return ctx;
}

static int proxy_http2_handler(request_rec *r, 
                               proxy_worker *worker,
                               proxy_server_conf *conf,
                               char *url, 
