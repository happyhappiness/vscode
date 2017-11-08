apr_status_t apr_setsocketopt(apr_socket_t *sock,
                              apr_int32_t opt, apr_int32_t on)
{
    return apr_socket_opt_set(sock, opt, on);
}