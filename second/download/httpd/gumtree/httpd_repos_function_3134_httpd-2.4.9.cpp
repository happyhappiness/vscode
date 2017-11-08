static int op_R(ap_expr_eval_ctx_t *ctx, const void *data, const char *arg1)
{
    apr_ipsubnet_t *subnet = (apr_ipsubnet_t *)data;

    AP_DEBUG_ASSERT(subnet != NULL);

    if (!ctx->r)
        return FALSE;

    return apr_ipsubnet_test(subnet, ctx->r->useragent_addr);
}