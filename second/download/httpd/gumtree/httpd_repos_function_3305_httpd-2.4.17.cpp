static authz_status ip_check_authorization(request_rec *r,
                                           const char *require_line,
                                           const void *parsed_require_line)
{
    /* apr_ipsubnet_test should accept const but doesn't */
    apr_ipsubnet_t **ip = (apr_ipsubnet_t **)parsed_require_line;

    while (*ip) {
        if (apr_ipsubnet_test(*ip, r->useragent_addr))
            return AUTHZ_GRANTED;
        ip++;
    }

    /* authz_core will log the require line and the result at DEBUG */
    return AUTHZ_DENIED;
}