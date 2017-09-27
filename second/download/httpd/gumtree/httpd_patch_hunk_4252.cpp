         
         /* Install the connection input filter that feeds the session */
         session->cin = h2_filter_cin_create(session->pool, 
                                             h2_session_receive, session);
         ap_add_input_filter("H2_IN", session->cin, r, c);
 
-        h2_conn_io_init(&session->io, c, session->config, session->pool);
+        h2_conn_io_init(&session->io, c, session->config);
         session->bbtmp = apr_brigade_create(session->pool, c->bucket_alloc);
         
         status = init_callbacks(c, &callbacks);
         if (status != APR_SUCCESS) {
             ap_log_cerror(APLOG_MARK, APLOG_ERR, status, c, APLOGNO(02927) 
                           "nghttp2: error in init_callbacks");
