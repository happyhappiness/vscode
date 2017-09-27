                                                &echo_module);
     pConfig->bEnabled = arg;
 
     return NULL;
 }
 
+static apr_status_t brigade_peek(apr_bucket_brigade *bbIn,
+                                 char *buff, apr_size_t bufflen)
+{
+    apr_bucket *b;
+    apr_size_t readbytes = 0;
+
+    if (bufflen--)
+        /* compensate for NULL */
+        *buff = '\0';
+    else
+        return APR_EGENERAL;
+
+    if (APR_BRIGADE_EMPTY(bbIn))
+        return APR_EGENERAL;
+
+    b = APR_BRIGADE_FIRST(bbIn);
+
+    while ((b != APR_BRIGADE_SENTINEL(bbIn)) && (readbytes < bufflen)) {
+        const char *pos;
+        const char *str;
+        apr_size_t len;
+        apr_status_t rv;
+
+        if ((rv = apr_bucket_read(b, &str, &len, APR_NONBLOCK_READ))
+                != APR_SUCCESS)
+            return rv;
+
+        if ((pos = memchr(str, APR_ASCII_LF, len)) != NULL)
+            len = pos - str;
+        if (len > bufflen - readbytes)
+            len = bufflen - readbytes;
+        memcpy (buff + readbytes, str, len);
+        readbytes += len;
+        buff[readbytes] = '\0';
+
+        b = APR_BUCKET_NEXT(b);
+    }
+    return APR_SUCCESS;
+}
+
+
+static int update_echo_child_status(ap_sb_handle_t *sbh, 
+                                    int status, conn_rec *c,
+                                    apr_bucket_brigade *last_echoed)
+{
+    worker_score *ws = ap_get_scoreboard_worker(sbh);
+    int old_status = ws->status;
+
+    ws->status = status;
+
+    if (!ap_extended_status)
+        return old_status;
+
+    ws->last_used = apr_time_now();
+
+    /* initial pass only, please - in the name of efficiency */
+    if (c) {
+        apr_cpystrn(ws->client, 
+                    ap_get_remote_host(c, c->base_server->lookup_defaults,
+                                       REMOTE_NOLOOKUP, NULL),
+                    sizeof(ws->client));
+        apr_cpystrn(ws->vhost, c->base_server->server_hostname,
+                    sizeof(ws->vhost));
+        /* Deliberate trailing space - filling in string on WRITE passes */
+        apr_cpystrn(ws->request, "ECHO ", sizeof(ws->request));
+    }
+
+    /* each subsequent WRITE pass, let's update what we echoed */
+    if (last_echoed) {
+        brigade_peek(last_echoed, ws->request + sizeof("ECHO ") - 1, 
+                     sizeof(ws->request) - sizeof("ECHO ") + 1);
+    }
+
+    return old_status;
+}
+
 static int process_echo_connection(conn_rec *c)
 {
     apr_bucket_brigade *bb;
     apr_bucket *b;
-    apr_status_t rv;
+    apr_socket_t *csd = NULL;
     EchoConfig *pConfig = ap_get_module_config(c->base_server->module_config,
                                                &echo_module);
 
     if (!pConfig->bEnabled) {
         return DECLINED;
     }
+    
+    ap_time_process_request(c->sbh, START_PREQUEST);
+    update_echo_child_status(c->sbh, SERVER_BUSY_READ, c, NULL);
 
-    do {
-        bb = apr_brigade_create(c->pool, c->bucket_alloc);
+    bb = apr_brigade_create(c->pool, c->bucket_alloc);
+
+    for ( ; ; ) {
+        apr_status_t rv;
 
         /* Get a single line of input from the client */
         if (((rv = ap_get_brigade(c->input_filters, bb, AP_MODE_GETLINE,
-                                 APR_BLOCK_READ, 0)) != APR_SUCCESS) ||
-             APR_BRIGADE_EMPTY(bb)) {
-            apr_brigade_destroy(bb);
+                                  APR_BLOCK_READ, 0)) != APR_SUCCESS)) {
+            apr_brigade_cleanup(bb);
+            if (!APR_STATUS_IS_EOF(rv) && ! APR_STATUS_IS_TIMEUP(rv))
+                ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server,
+                             "ProtocolEcho: Failure reading from %s",
+                             c->remote_ip);
+            break;
+        }
+
+        /* Something horribly wrong happened.  Someone didn't block! */
+        if (APR_BRIGADE_EMPTY(bb)) {
+            apr_brigade_cleanup(bb);
+            ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server,
+                         "ProtocolEcho: Error - read empty brigade from %s!",
+                         c->remote_ip);
             break;
         }
 
+        if (!csd) {
+            csd = ap_get_module_config(c->conn_config, &core_module);
+            apr_socket_timeout_set(csd, c->base_server->keep_alive_timeout);
+        }
+
+        update_echo_child_status(c->sbh, SERVER_BUSY_WRITE, NULL, bb);
+
         /* Make sure the data is flushed to the client */
         b = apr_bucket_flush_create(c->bucket_alloc);
         APR_BRIGADE_INSERT_TAIL(bb, b);
-
-        /* Send back the data. */
         rv = ap_pass_brigade(c->output_filters, bb);
-    } while (rv == APR_SUCCESS);
+        if (rv != APR_SUCCESS) {
+            ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server,
+                         "ProtocolEcho: Failure writing to %s",
+                         c->remote_ip);
+            break; 
+        }
+        apr_brigade_cleanup(bb);
 
+        /* Announce our intent to loop */
+        update_echo_child_status(c->sbh, SERVER_BUSY_KEEPALIVE, NULL, NULL);
+    }
+    apr_brigade_destroy(bb);
+    ap_time_process_request(c->sbh, STOP_PREQUEST);
+    update_echo_child_status(c->sbh, SERVER_CLOSING, c, NULL);
     return OK;
 }
 
 static const command_rec echo_cmds[] =
 {
     AP_INIT_FLAG("ProtocolEcho", echo_on, NULL, RSRC_CONF,
