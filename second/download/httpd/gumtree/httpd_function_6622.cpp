const char *h2_proxy_link_reverse_map(request_rec *r,
                                      proxy_dir_conf *conf, 
                                      const char *real_backend_uri,
                                      const char *proxy_server_uri,
                                      const char *s)
{
    link_ctx ctx;
    
    if (r->proxyreq != PROXYREQ_REVERSE) {
        return s;
    }
    memset(&ctx, 0, sizeof(ctx));
    ctx.r = r;
    ctx.pool = r->pool;
    ctx.conf = conf;
    ctx.real_backend_uri = real_backend_uri;
    ctx.rbu_len = (int)strlen(ctx.real_backend_uri);
    ctx.p_server_uri = proxy_server_uri;
    ctx.psu_len = (int)strlen(ctx.p_server_uri);
    ctx.s = s;
    ctx.slen = (int)strlen(s);
    while (read_link(&ctx)) {
        while (skip_param(&ctx)) {
            /* nop */
        }
        map_link(&ctx);
        if (!read_sep(&ctx)) {
            break;
        }
    }
    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, 
                  "link_reverse_map %s --> %s", s, ctx.s);
    return ctx.s;
}