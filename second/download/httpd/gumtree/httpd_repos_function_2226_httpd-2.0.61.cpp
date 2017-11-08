static int perchild_process_connection(conn_rec *c)
{
    ap_filter_t *f;
    apr_bucket_brigade *bb;
    core_net_rec *net;

    apr_pool_userdata_get((void **)&bb, "PERCHILD_SOCKETS", c->pool);
    if (bb != NULL) {
        for (f = c->output_filters; f != NULL; f = f->next) {
            if (!strcmp(f->frec->name, "core")) {
                break;
            }
        }
        if (f != NULL) {
            net = f->ctx;
            net->in_ctx = apr_palloc(c->pool, sizeof(*net->in_ctx));
            net->in_ctx->b = bb;
        }
    }
    return DECLINED;
}