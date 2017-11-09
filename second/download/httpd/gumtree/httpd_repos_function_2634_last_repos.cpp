int h2_proxy_res_ignore_header(const char *name, size_t len)
{
    return (h2_proxy_req_ignore_header(name, len) 
            || ignore_header(H2_LIT_ARGS(IgnoredProxyRespHds), name, len));
}