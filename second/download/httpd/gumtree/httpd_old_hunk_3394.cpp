             * shutdown() to work
             */
            if (setsockopt(context->accept_socket, SOL_SOCKET,
                           SO_UPDATE_ACCEPT_CONTEXT, (char *)&nlsd,
                           sizeof(nlsd))) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(),
                             ap_server_conf,
                             "setsockopt(SO_UPDATE_ACCEPT_CONTEXT) failed.");
                /* Not a failure condition. Keep running. */
            }

            /* Get the local & remote address 
             * TODO; error check
             */
            GetAcceptExSockaddrs(buf, len, PADDED_ADDR_SIZE, PADDED_ADDR_SIZE,
                                 &context->sa_server, &context->sa_server_len,
                                 &context->sa_client, &context->sa_client_len);

            /* For 'data', craft a bucket for our data result 
             * and pass to worker_main as context->overlapped.Pointer
             */
            if (accf == 2 && BytesRead)
            {
                apr_bucket *b;
                b = apr_bucket_heap_create(buf, APR_BUCKET_BUFF_SIZE,
