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
