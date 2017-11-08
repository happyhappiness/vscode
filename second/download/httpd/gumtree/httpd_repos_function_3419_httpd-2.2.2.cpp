apr_status_t apr_socket_opt_get(apr_socket_t *sock, 
                                apr_int32_t opt, apr_int32_t *on)
{
    switch(opt) {
        default:
            *on = apr_is_option_set(sock, opt);
    }
    return APR_SUCCESS;
}