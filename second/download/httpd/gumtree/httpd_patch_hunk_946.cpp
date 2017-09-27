     r->read_length     = 0;
     r->read_body       = REQUEST_NO_BODY;
 
     r->status          = HTTP_REQUEST_TIME_OUT;  /* Until we get a request */
     r->the_request     = NULL;
 
+    /* Begin by presuming any module can make its own path_info assumptions,
+     * until some module interjects and changes the value.
+     */
+    r->used_path_info = AP_REQ_DEFAULT_PATH_INFO;
+
     tmp_bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
 
     /* Get the request... */
     if (!read_request_line(r, tmp_bb)) {
         if (r->status == HTTP_REQUEST_URI_TOO_LARGE) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
