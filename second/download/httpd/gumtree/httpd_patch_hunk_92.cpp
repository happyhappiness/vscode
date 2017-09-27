     env = ap_create_environment(r->pool, r->subprocess_env); 
 
     if ((retval = connect_to_daemon(&sd, r, conf)) != OK) {
         return retval;
     }
 
-    send_req(sd, r, argv0, env, CGI_REQ); 
+    rv = send_req(sd, r, argv0, env, CGI_REQ); 
+    if (rv != APR_SUCCESS) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+                     "write to cgi daemon process");
+    }
 
+    info = apr_palloc(r->pool, sizeof(struct cleanup_script_info));
+    info->r = r;
+    info->conn_id = r->connection->id;
+    info->conf = conf;
+    apr_pool_cleanup_register(r->pool, info,
+                              cleanup_script,
+                              apr_pool_cleanup_null);
     /* We are putting the socket discriptor into an apr_file_t so that we can
      * use a pipe bucket to send the data to the client.
      * Note that this does not register a cleanup for the socket.  We did
      * that explicitly right after we created the socket.
      */
-    apr_os_file_put(&tempsock, &sd, 0, r->pool);
+    apr_os_pipe_put(&tempsock, &sd, r->pool);
 
     if ((argv0 = strrchr(r->filename, '/')) != NULL) 
         argv0++; 
     else 
         argv0 = r->filename; 
 
