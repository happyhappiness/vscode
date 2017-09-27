                   pid);
     kill(pid, SIGKILL);
 
     return APR_EGENERAL;
 }
 
-static apr_status_t cleanup_script(void *vptr)
-{
-    struct cleanup_script_info *info = vptr;
-    int sd;
-    int rc;
+static apr_status_t get_cgi_pid(request_rec *r,  cgid_server_conf *conf, pid_t *pid) { 
     cgid_req_t req = {0};
-    pid_t pid;
     apr_status_t stat;
+    int rc, sd;
 
-    rc = connect_to_daemon(&sd, info->r, info->conf);
+    rc = connect_to_daemon(&sd, r, conf);
     if (rc != OK) {
         return APR_EGENERAL;
     }
 
-    /* we got a socket, and there is already a cleanup registered for it */
-
     req.req_type = GETPID_REQ;
     req.ppid = parent_pid;
-    req.conn_id = info->r->connection->id;
+    req.conn_id = r->connection->id;
 
     stat = sock_write(sd, &req, sizeof(req));
     if (stat != APR_SUCCESS) {
         return stat;
     }
 
     /* wait for pid of script */
-    stat = sock_read(sd, &pid, sizeof(pid));
+    stat = sock_read(sd, pid, sizeof(*pid));
     if (stat != APR_SUCCESS) {
         return stat;
     }
 
     if (pid == 0) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, info->r, APLOGNO(01261)
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01261)
                       "daemon couldn't find CGI process for connection %lu",
-                      info->conn_id);
+                      r->connection->id);
         return APR_EGENERAL;
     }
-    return cleanup_nonchild_process(info->r, pid);
+
+    return APR_SUCCESS;
+}
+
+
+static apr_status_t cleanup_script(void *vptr)
+{
+    struct cleanup_script_info *info = vptr;
+    return cleanup_nonchild_process(info->r, info->pid);
 }
 
 static int cgid_handler(request_rec *r)
 {
     int retval, nph, dbpos;
     char *argv0, *dbuf;
