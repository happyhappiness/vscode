static const char *get_server_name_for_url(request_rec *r)
{
    const char *plain_server_name = ap_get_server_name(r);

#if APR_HAVE_IPV6
    if (ap_strchr_c(plain_server_name, ':')) { /* IPv6 literal? */
        return apr_psprintf(r->pool, "[%s]", plain_server_name);
    }
#endif
    return plain_server_name;
}