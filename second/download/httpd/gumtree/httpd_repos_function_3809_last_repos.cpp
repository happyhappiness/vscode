static authz_status local_check_authorization(request_rec *r,
                                              const char *require_line,
                                              const void *parsed_require_line)
{
     if (   apr_sockaddr_equal(r->connection->local_addr,
                               r->useragent_addr)
         || apr_ipsubnet_test(localhost_v4, r->useragent_addr)
#if APR_HAVE_IPV6
         || apr_ipsubnet_test(localhost_v6, r->useragent_addr)
#endif
        )
     {
        return AUTHZ_GRANTED;
     }

     return AUTHZ_DENIED;
}