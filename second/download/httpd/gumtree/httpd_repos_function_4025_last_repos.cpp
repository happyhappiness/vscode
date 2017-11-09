static const char *conn_var_fn(ap_expr_eval_ctx_t *ctx, const void *data)
{
    int index = ((const char **)data - conn_var_names);
    conn_rec *c = ctx->c;
    if (!c)
        return "";

    switch (index) {
    case 0:
        if (is_https && is_https(c))
            return "on";
        else
            return "off";
    case 1:
#if APR_HAVE_IPV6
        {
            apr_sockaddr_t *addr = c->client_addr;
            if (addr->family == AF_INET6
                && !IN6_IS_ADDR_V4MAPPED((struct in6_addr *)addr->ipaddr_ptr))
                return "on";
            else
                return "off";
        }
#else
        return "off";
#endif
    case 2:
        return c->log_id;
    case 3:
        return c->client_ip;
    case 4:
        if (is_http2 && is_http2(c))
            return "on";
        else
            return "off";
    default:
        ap_assert(0);
        return NULL;
    }
}