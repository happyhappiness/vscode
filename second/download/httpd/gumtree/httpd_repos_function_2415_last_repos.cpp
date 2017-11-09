static const char *val_H2_STREAM_TAG(apr_pool_t *p, server_rec *s,
                                     conn_rec *c, request_rec *r, h2_ctx *ctx)
{
    if (ctx) {
        h2_task *task = h2_ctx_get_task(ctx);
        if (task) {
            return task->id;
        }
    }
    return "";
}