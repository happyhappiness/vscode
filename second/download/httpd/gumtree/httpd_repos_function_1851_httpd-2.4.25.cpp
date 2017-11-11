static APR_INLINE int check_headers(request_rec *r)
{
    struct check_header_ctx ctx;
    core_server_config *conf =
            ap_get_core_module_config(r->server->module_config);

    ctx.r = r;
    ctx.strict = (conf->http_conformance != AP_HTTP_CONFORMANCE_UNSAFE);
    return apr_table_do(check_header, &ctx, r->headers_out, NULL) &&
           apr_table_do(check_header, &ctx, r->err_headers_out, NULL);
}