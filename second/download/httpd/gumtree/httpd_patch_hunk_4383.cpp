         }
         
         status = ap_get_brigade(session->c->input_filters, session->input, 
                                 AP_MODE_READBYTES, 
                                 block? APR_BLOCK_READ : APR_NONBLOCK_READ, 
                                 64 * 1024);
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, session->c, 
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, session->c, 
                       "h2_proxy_session(%s): read from conn", session->id);
         if (socket && save_timeout != -1) {
             apr_socket_timeout_set(socket, save_timeout);
         }
     }
     
