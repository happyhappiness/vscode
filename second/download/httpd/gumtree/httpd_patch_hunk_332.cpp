 #define READ_BLOCKSIZE 2048
 
 
 AP_DECLARE(int) ap_xml_parse_input(request_rec * r, apr_xml_doc **pdoc)
 {
     apr_xml_parser *parser;
-    int result;
+    apr_bucket_brigade *brigade;
+    int seen_eos;
     apr_status_t status;
     char errbuf[200];
-
-    if ((result = ap_setup_client_block(r, REQUEST_CHUNKED_DECHUNK)) != OK)
-        return result;
-
-    if (r->remaining == 0) {
-        *pdoc = NULL;
-        return OK;
-    }
+    apr_size_t total_read = 0;
+    apr_size_t limit_xml_body = ap_get_limit_xml_body(r);
+    int result = HTTP_BAD_REQUEST;
 
     parser = apr_xml_parser_create(r->pool);
+    brigade = apr_brigade_create(r->pool, r->connection->bucket_alloc);
 
-    if (ap_should_client_block(r)) {
-        long len;
-        char *buffer;
-        apr_size_t total_read = 0;
-        apr_size_t limit_xml_body = ap_get_limit_xml_body(r);
+    seen_eos = 0;
+    total_read = 0;
 
-        /* allocate our working buffer */
-        buffer = apr_palloc(r->pool, READ_BLOCKSIZE);
+    do {
+        apr_bucket *bucket;
 
         /* read the body, stuffing it into the parser */
-        while ((len = ap_get_client_block(r, buffer, READ_BLOCKSIZE)) > 0) {
+        status = ap_get_brigade(r->input_filters, brigade,
+                                AP_MODE_READBYTES, APR_BLOCK_READ,
+                                READ_BLOCKSIZE);
+
+        if (status != APR_SUCCESS) {
+            goto read_error;
+        }
+
+        APR_BRIGADE_FOREACH(bucket, brigade) {
+            const char *data;
+            apr_size_t len;
+
+            if (APR_BUCKET_IS_EOS(bucket)) {
+                seen_eos = 1;
+                break;
+            }
+
+            if (APR_BUCKET_IS_METADATA(bucket)) {
+                continue;
+            }
+
+            status = apr_bucket_read(bucket, &data, &len, APR_BLOCK_READ);
+            if (status != APR_SUCCESS) {
+                goto read_error;
+            }
+
             total_read += len;
             if (limit_xml_body && total_read > limit_xml_body) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                               "XML request body is larger than the configured "
                               "limit of %lu", (unsigned long)limit_xml_body);
+                result = HTTP_REQUEST_ENTITY_TOO_LARGE;
                 goto read_error;
             }
 
-            status = apr_xml_parser_feed(parser, buffer, len);
-            if (status)
+            status = apr_xml_parser_feed(parser, data, len);
+            if (status) {
                 goto parser_error;
+            }
         }
-        if (len == -1) {
-            /* ap_get_client_block() has logged an error */
-            goto read_error;
-        }
-    }
+
+        apr_brigade_cleanup(brigade);
+    } while (!seen_eos);
+
+    apr_brigade_destroy(brigade);
 
     /* tell the parser that we're done */
     status = apr_xml_parser_done(parser, pdoc);
     if (status) {
+        /* Some parsers are stupid and return an error on blank documents. */
+        if (!total_read) {
+            *pdoc = NULL;
+            return OK;
+        }
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                       "XML parser error (at end). status=%d", status);
         return HTTP_BAD_REQUEST;
     }
 
     return OK;
