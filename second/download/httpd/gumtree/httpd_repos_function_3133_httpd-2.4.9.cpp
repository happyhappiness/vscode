static int op_ipmatch(ap_expr_eval_ctx_t *ctx, const void *data, const char *arg1,
                const char *arg2)
{
    apr_ipsubnet_t *subnet = (apr_ipsubnet_t *)data;
    apr_sockaddr_t *saddr;

    AP_DEBUG_ASSERT(subnet != NULL);

    /* maybe log an error if this goes wrong? */
    if (apr_sockaddr_info_get(&saddr, arg1, APR_UNSPEC, 0, 0, ctx->p) != APR_SUCCESS)
        return FALSE;

    return apr_ipsubnet_test(subnet, saddr);
}