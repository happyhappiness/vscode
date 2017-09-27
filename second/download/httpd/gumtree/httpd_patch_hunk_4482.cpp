                      "winnt_accept: getsockname error on listening socket, "
                      "is IPv6 available?");
         return 1;
    }
 #endif
 
-    if (accf > 0) /* 'data' or 'connect' */
+    if (accf > 0) /* 'connect' */
     {
         if (WSAIoctl(nlsd, SIO_GET_EXTENSION_FUNCTION_POINTER,
                      &GuidAcceptEx, sizeof GuidAcceptEx, 
                      &lpfnAcceptEx, sizeof lpfnAcceptEx, 
                      &BytesRead, NULL, NULL) == SOCKET_ERROR) {
             ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_netos_error(),
