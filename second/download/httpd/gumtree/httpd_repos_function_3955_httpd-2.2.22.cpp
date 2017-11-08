static int os2_socket_init(int domain, int type, int protocol)
{
    int rc = os2_fn_link();
    if (rc == APR_SUCCESS)
        return apr_os2_socket(domain, type, protocol);
    return rc;
}