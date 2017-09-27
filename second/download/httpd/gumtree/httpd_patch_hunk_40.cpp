     }
 
     child_info_table = (child_info_t *)apr_pcalloc(p, tmp_server_limit * sizeof(child_info_t));
     for (i = 0; i < tmp_server_limit; i++) {
         child_info_table[i].uid = -1;
         child_info_table[i].gid = -1;
-        child_info_table[i].sd = -1;
+        child_info_table[i].input = -1;
+        child_info_table[i].output = -1;
     }
 
     return OK;
 }
 
 static int pass_request(request_rec *r)
 {
+    int rv;
     apr_socket_t *thesock = ap_get_module_config(r->connection->conn_config, &core_module);
     struct msghdr msg;
     struct cmsghdr *cmsg;
     int sfd;
-    struct iovec iov;
+    struct iovec iov[2];
     conn_rec *c = r->connection;
     apr_bucket_brigade *bb = apr_brigade_create(r->pool, c->bucket_alloc);
-    perchild_server_conf *sconf = (perchild_server_conf *)
-                            ap_get_module_config(r->server->module_config, 
-                                                 &mpm_perchild_module);
-    char request_body[HUGE_STRING_LEN];
+    apr_bucket_brigade *sockbb;
+    char request_body[HUGE_STRING_LEN] = "\0";
     apr_off_t len = 0;
     apr_size_t l = 0;
     perchild_header h;
+    apr_bucket *sockbuck;
+    perchild_server_conf *sconf = (perchild_server_conf *)
+                            ap_get_module_config(r->server->module_config, 
+                                                 &mpm_perchild_module);
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, 
-                 "passing request to another child.  Vhost: %s, child %d",
-                 apr_table_get(r->headers_in, "Host"), child_num);
-    ap_get_brigade(r->input_filters, bb, AP_MODE_EXHAUSTIVE, APR_NONBLOCK_READ,
+                 "passing request to another child.  Vhost: %s, child %d %d",
+                 apr_table_get(r->headers_in, "Host"), child_num, sconf->output);
+    ap_get_brigade(r->connection->input_filters, bb, AP_MODE_EXHAUSTIVE, APR_NONBLOCK_READ,
                    len);
+
+    for (sockbuck = APR_BRIGADE_FIRST(bb); sockbuck != APR_BRIGADE_SENTINEL(bb);
+         sockbuck = APR_BUCKET_NEXT(sockbuck)) {
+        if (APR_BUCKET_IS_SOCKET(sockbuck)) {
+            break;
+        }
+    }
+    
+    if (!sockbuck) {
+    }
+    sockbb = apr_brigade_split(bb, sockbuck); 
+
     if (apr_brigade_flatten(bb, request_body, &l) != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, 
+                     "Unable to flatten brigade, declining request");
         return DECLINED;
     }
 
     apr_os_sock_get(&sfd, thesock);
 
-    iov.iov_base = "FOOBAR";
-    iov.iov_len = 1;
+    h.p = r->pool;
+    h.headers = apr_pstrcat(h.p, r->the_request, CRLF, "Host: ", r->hostname, 
+                            CRLF, NULL);
+/* XXX  This REALLY needs to be uncommented, but it is causing problems.
+    apr_table_do((int (*) (void *, const char *, const char *))
+                 perchild_header_field, (void *) &h, r->headers_in, NULL); */
+    h.headers = apr_pstrcat(h.p, h.headers, CRLF, NULL);
+
+    iov[0].iov_base = h.headers;
+    iov[0].iov_len = strlen(h.headers) + 1;
+    iov[1].iov_base = request_body;
+    iov[1].iov_len = len + 1;
 
     msg.msg_name = NULL;
     msg.msg_namelen = 0;
-    msg.msg_iov = &iov;
-    msg.msg_iovlen = 1;
+    msg.msg_iov = iov;
+    msg.msg_iovlen = 2;
 
     cmsg = apr_palloc(r->pool, sizeof(*cmsg) + sizeof(sfd));
-    cmsg->cmsg_len = sizeof(*cmsg) + sizeof(int);
+    cmsg->cmsg_len = sizeof(*cmsg) + sizeof(sfd);
     cmsg->cmsg_level = SOL_SOCKET;
     cmsg->cmsg_type = SCM_RIGHTS;
 
     memcpy(CMSG_DATA(cmsg), &sfd, sizeof(sfd));
 
-    msg.msg_control = (caddr_t)cmsg;
+    msg.msg_control = cmsg;
     msg.msg_controllen = cmsg->cmsg_len;
-    msg.msg_flags=0;
 
-    if (sendmsg(sconf->sd2, &msg, 0) == -1) {
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, 
+                 "Writing message to %d, passing sd:  %d", sconf->output, sfd);
+
+    if ((rv = sendmsg(sconf->output, &msg, 0)) == -1) {
         apr_pool_destroy(r->pool);
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, 
+                 "Writing message failed %d %d", rv, errno);
         return -1;
     }
 
-    h.p = r->pool;
-    h.headers = apr_pstrdup(h.p, r->the_request);
-    apr_table_do((int (*) (void *, const char *, const char *))
-                 perchild_header_field, (void *) &h, r->headers_in, NULL);
-
-    write(sconf->sd2, h.headers, strlen(h.headers));
-    write(sconf->sd2, request_body, len);
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, 
+                 "Writing message succeeded %d", rv);
 
     apr_pool_destroy(r->pool);
     return 1;
 }
 
 static char *make_perchild_socket(const char *fullsockname, int sd[2])
