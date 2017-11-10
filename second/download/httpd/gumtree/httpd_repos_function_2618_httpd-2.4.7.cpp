static const char *nwssl_hook_http_scheme(const request_rec *r)
{
    if (isSecure(r) && !isSecureUpgraded(r))
        return "https";

    return NULL;
}