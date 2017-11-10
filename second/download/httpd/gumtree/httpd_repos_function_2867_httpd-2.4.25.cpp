static int h2_h2_pre_close_conn(conn_rec *c)
{
    h2_ctx *ctx;

    /* slave connection? */
    if (c->master) {
        return DECLINED;
    }

    ctx = h2_ctx_get(c, 0);
    if (ctx) {
        /* If the session has been closed correctly already, we will not
         * fiond a h2_ctx here. The presence indicates that the session
         * is still ongoing. */
        return h2_conn_pre_close(ctx, c);
    }
    return DECLINED;
}