     int sfd;
     struct iovec iov[2];
     conn_rec *c = r->connection;
     apr_bucket_brigade *bb = apr_brigade_create(r->pool, c->bucket_alloc);
     apr_bucket_brigade *sockbb;
     char request_body[HUGE_STRING_LEN] = "\0";
-    apr_off_t len = 0;
-    apr_size_t l = 0;
+    apr_size_t l = sizeof(request_body);
     perchild_header h;
     apr_bucket *sockbuck;
     perchild_server_conf *sconf = (perchild_server_conf *)
                             ap_get_module_config(r->server->module_config, 
                                                  &mpm_perchild_module);
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, 
                  "passing request to another child.  Vhost: %s, child %d %d",
                  apr_table_get(r->headers_in, "Host"), child_num, sconf->output);
     ap_get_brigade(r->connection->input_filters, bb, AP_MODE_EXHAUSTIVE, APR_NONBLOCK_READ,
-                   len);
+                   0);
 
     for (sockbuck = APR_BRIGADE_FIRST(bb); sockbuck != APR_BRIGADE_SENTINEL(bb);
          sockbuck = APR_BUCKET_NEXT(sockbuck)) {
         if (APR_BUCKET_IS_SOCKET(sockbuck)) {
             break;
         }
