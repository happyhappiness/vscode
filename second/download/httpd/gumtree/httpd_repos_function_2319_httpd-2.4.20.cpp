static const char *val_H2_PUSH(apr_pool_t *p, server_rec *s,
                               conn_rec *c, request_rec *r, h2_ctx *ctx)
{
    if (ctx) {
        if (r) {
            h2_task *task = h2_ctx_get_task(ctx);
            if (task && task->request->push_policy != H2_PUSH_NONE) {
                return "on";
            }
        }
        else if (c && h2_session_push_enabled(ctx->session)) {
            return "on";
        }
    }
    else if (s) {
        const h2_config *cfg = h2_config_sget(s);
        if (cfg && h2_config_geti(cfg, H2_CONF_PUSH)) {
            return "on";
        }
    }
    return "off";
}