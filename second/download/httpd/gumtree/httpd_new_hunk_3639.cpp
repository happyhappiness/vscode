                               forward->proxy_auth);
    }
    /* Set a reasonable agent and send everything */
    nbytes += apr_snprintf(buffer + nbytes, sizeof(buffer) - nbytes,
                           "Proxy-agent: %s" CRLF CRLF,
                           ap_get_server_banner());
    ap_xlate_proto_to_ascii(buffer, nbytes);
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
        if (strstr(buffer + len - nbytes, CRLF_ASCII CRLF_ASCII) != NULL) {
            ap_xlate_proto_from_ascii(buffer, len);
            complete = 1;
            break;
        }
    } while (status == APR_SUCCESS && left > 0);
    /* Drain what's left */
    if (!complete) {
        nbytes = sizeof(drain_buffer) - 1;
        while (status == APR_SUCCESS && nbytes) {
            status = apr_socket_recv(backend->sock, drain_buffer, &nbytes);
            drain_buffer[nbytes] = '\0';
            nbytes = sizeof(drain_buffer) - 1;
            if (strstr(drain_buffer, CRLF_ASCII CRLF_ASCII) != NULL) {
                break;
            }
        }
    }

    /* Check for HTTP_OK response status */
    if (status == APR_SUCCESS) {
        unsigned int major, minor;
        /* Only scan for three character status code */
        char code_str[4];

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00949)
                     "send_http_connect: response from the forward proxy: %s",
                     buffer);
