     ajp_msg_t *msg;
     apr_size_t bufsiz;
     char *buff;
     apr_uint16_t size;
     const char *tenc;
     int havebody = 1;
-    int isok = 1;
+    int output_failed = 0;
+    int backend_failed = 0;
     apr_off_t bb_len;
     int data_sent = 0;
     int rv = 0;
     apr_int32_t conn_poll_fd;
     apr_pollfd_t *conn_poll;
-
+    proxy_server_conf *psf =
+    ap_get_module_config(r->server->module_config, &proxy_module);
+    apr_size_t maxsize = AJP_MSG_BUFFER_SZ;
+
+    if (psf->io_buffer_size_set)
+       maxsize = psf->io_buffer_size;
+    if (maxsize > AJP_MAX_BUFFER_SZ)
+       maxsize = AJP_MAX_BUFFER_SZ;
+    else if (maxsize < AJP_MSG_BUFFER_SZ)
+       maxsize = AJP_MSG_BUFFER_SZ;
+    maxsize = APR_ALIGN(maxsize, 1024);
+       
     /*
      * Send the AJP request to the remote server
      */
 
     /* send request headers */
-    status = ajp_send_header(conn->sock, r, uri);
+    status = ajp_send_header(conn->sock, r, maxsize, uri);
     if (status != APR_SUCCESS) {
         conn->close++;
         ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                      "proxy: AJP: request failed to %pI (%s)",
                      conn->worker->cp->addr,
                      conn->worker->hostname);
