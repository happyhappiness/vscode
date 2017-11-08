static apr_port_t nwssl_hook_default_port(const request_rec *r)
{
    if (isSecure(r))
        return DEFAULT_HTTPS_PORT;

    return 0;
}