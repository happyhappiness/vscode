static APR_INLINE int check_headers(request_rec *r)
{
    struct check_header_ctx ctx;
    core_server_config *conf =
        (core_server_config *)ap_get_module_config(r->server->module_config,
                                                   &core_module);

    ctx.r = r;
    ctx.strict = (conf->http_conformance != AP_HTTP_CONFORMANCE_UNSAFE);
    return check_headers_table(r->headers_out, &ctx) &&
           check_headers_table(r->err_headers_out, &ctx);
}