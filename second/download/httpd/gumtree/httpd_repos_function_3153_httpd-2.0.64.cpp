apr_status_t apr_socket_opt_get(apr_socket_t *sock, 
                                apr_int32_t opt, apr_int32_t *on)
{
    switch(opt) {
        case APR_SO_TIMEOUT:
            /* XXX: To be deprecated */
            *on = (apr_int32_t)sock->timeout;
            break;
        default:
            *on = apr_is_option_set(sock->netmask, opt);
    }
    return APR_SUCCESS;
}