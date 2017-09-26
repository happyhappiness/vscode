        return 0;
    else
        return 1;
}
#endif /* USE_ALTERNATE_IS_CONNECTED */


/*
 * Send a HTTP CONNECT request to a forward proxy.
 * The proxy is given by "backend", the target server
 * is contained in the "forward" member of "backend".
 */
static apr_status_t send_http_connect(proxy_conn_rec *backend,
                                      server_rec *s)
{
    int status;
    apr_size_t nbytes;
    apr_size_t left;
    int complete = 0;
    char buffer[HUGE_STRING_LEN];
    char drain_buffer[HUGE_STRING_LEN];
    forward_info *forward = (forward_info *)backend->forward;
    int len = 0;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "proxy: CONNECT: sending the CONNECT request for %s:%d "
                 "to the remote proxy %pI (%s)",
                 forward->target_host, forward->target_port,
                 backend->addr, backend->hostname);
    /* Create the CONNECT request */
    nbytes = apr_snprintf(buffer, sizeof(buffer),
                          "CONNECT %s:%d HTTP/1.0" CRLF,
                          forward->target_host, forward->target_port);
    /* Add proxy authorization from the initial request if necessary */
    if (forward->proxy_auth != NULL) {
        nbytes += apr_snprintf(buffer + nbytes, sizeof(buffer) - nbytes,
                               "Proxy-Authorization: %s" CRLF,
                               forward->proxy_auth);
    }
    /* Set a reasonable agent and send everything */
    nbytes += apr_snprintf(buffer + nbytes, sizeof(buffer) - nbytes,
                           "Proxy-agent: %s" CRLF CRLF,
                           ap_get_server_banner());
    apr_socket_send(backend->sock, buffer, &nbytes);

    /* Receive the whole CONNECT response */
    left = sizeof(buffer) - 1;
    /* Read until we find the end of the headers or run out of buffer */
    do {
        nbytes = left;
        status = apr_socket_recv(backend->sock, buffer + len, &nbytes);
        len += nbytes;
        left -= nbytes;
        buffer[len] = '\0';
        if (strstr(buffer + len - nbytes, "\r\n\r\n") != NULL) {
            complete = 1;
            break;
        }
    } while (status == APR_SUCCESS && left > 0);
    /* Drain what's left */
    if (!complete) {
        nbytes = sizeof(drain_buffer) - 1;
        while (status == APR_SUCCESS && nbytes) {
            status = apr_socket_recv(backend->sock, drain_buffer, &nbytes);
            buffer[nbytes] = '\0';
            nbytes = sizeof(drain_buffer) - 1;
            if (strstr(drain_buffer, "\r\n\r\n") != NULL) {
                complete = 1;
                break;
            }
        }
    }

    /* Check for HTTP_OK response status */
    if (status == APR_SUCCESS) {
        int major, minor;
        /* Only scan for three character status code */
        char code_str[4];

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "send_http_connect: response from the forward proxy: %s",
                     buffer);

        /* Extract the returned code */
        if (sscanf(buffer, "HTTP/%u.%u %3s", &major, &minor, code_str) == 3) {
            status = atoi(code_str);
            if (status == HTTP_OK) {
                status = APR_SUCCESS;
            }
            else {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                             "send_http_connect: the forward proxy returned code is '%s'",
                             code_str);
            status = APR_INCOMPLETE;
            }
        }
    }

    return(status);
}


PROXY_DECLARE(int) ap_proxy_connect_backend(const char *proxy_function,
                                            proxy_conn_rec *conn,
                                            proxy_worker *worker,
                                            server_rec *s)
{
    apr_status_t rv;
