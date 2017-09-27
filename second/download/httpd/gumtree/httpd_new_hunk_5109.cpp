        return 1;
   }
#endif

    if (accf > 0) /* 'data' or 'connect' */
    {
        if (WSAIoctl(nlsd, SIO_GET_EXTENSION_FUNCTION_POINTER,
                     &GuidAcceptEx, sizeof GuidAcceptEx, 
                     &lpfnAcceptEx, sizeof lpfnAcceptEx, 
                     &BytesRead, NULL, NULL) == SOCKET_ERROR) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_netos_error(),
                         ap_server_conf, APLOGNO(02322)
                         "winnt_accept: failed to retrieve AcceptEx, try 'AcceptFilter none'");
            return 1;
        }
        if (WSAIoctl(nlsd, SIO_GET_EXTENSION_FUNCTION_POINTER,
                     &GuidGetAcceptExSockaddrs, sizeof GuidGetAcceptExSockaddrs,
                     &lpfnGetAcceptExSockaddrs, sizeof lpfnGetAcceptExSockaddrs,
                     &BytesRead, NULL, NULL) == SOCKET_ERROR) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_netos_error(),
                         ap_server_conf, APLOGNO(02323)
                         "winnt_accept: failed to retrieve GetAcceptExSockaddrs, try 'AcceptFilter none'");
            return 1;
        }
        /* first, high priority event is an already accepted connection */
        events[1] = exit_event;
        events[2] = max_requests_per_child_event;
    }
    else /* accf == 0, 'none' */
    {
