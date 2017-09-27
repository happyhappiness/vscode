             kill(*sd, SIGHUP); /* send signal to daemon telling it to die */
             break;
     }
 }
 #endif
 
-static int get_req(int fd, request_rec *r, char **argv0, char ***env, int *req_type) 
+/* deal with incomplete reads and signals
+ * assume you really have to read buf_size bytes
+ */
+static apr_status_t sock_read(int fd, void *vbuf, size_t buf_size)
+{
+    char *buf = vbuf;
+    int rc;
+    size_t bytes_read = 0;
+
+    do {
+        do {
+            rc = read(fd, buf + bytes_read, buf_size - bytes_read);
+        } while (rc < 0 && errno == EINTR);
+        switch(rc) {
+        case -1:
+            return errno;
+        case 0: /* unexpected */
+            return ECONNRESET;
+        default:
+            bytes_read += rc;
+        }
+    } while (bytes_read < buf_size);
+
+    return APR_SUCCESS;
+}
+
+/* deal with signals
+ */
+static apr_status_t sock_write(int fd, const void *buf, size_t buf_size)
+{
+    int rc;
+
+    do {
+        rc = write(fd, buf, buf_size);
+    } while (rc < 0 && errno == EINTR);
+    if (rc < 0) {
+        return errno;
+    }
+
+    return APR_SUCCESS;
+}
+
+static apr_status_t get_req(int fd, request_rec *r, char **argv0, char ***env, 
+                            cgid_req_t *req)
 { 
-    int i, len, j, rc; 
-    unsigned char *data; 
+    int i; 
+    char *user;
     char **environ; 
     core_dir_config *temp_core; 
-    void **dconf; 
-    module *suexec_mod = ap_find_linked_module("mod_suexec.c");
+    void **dconf;
+    apr_status_t stat;
 
     r->server = apr_pcalloc(r->pool, sizeof(server_rec)); 
 
-    rc = read(fd, req_type, sizeof(int));
-    if (rc != sizeof(int)) {
-        return 1;
+    /* read the request header */
+    stat = sock_read(fd, req, sizeof(*req));
+    if (stat != APR_SUCCESS) {
+        return stat;
     }
-    rc = read(fd, &j, sizeof(int));
-    if (rc != sizeof(int)) {
-        return 1;
-    }
-    rc = read(fd, &len, sizeof(int));
-    if (rc != sizeof(int)) {
-        return 1;
+    if (req->req_type == GETPID_REQ) {
+        /* no more data sent for this request */
+        return APR_SUCCESS;
     }
 
-    data = apr_pcalloc(r->pool, len + 1); /* get a cleared byte for final '\0' */
-    rc = read(fd, data, len); 
-    if (rc != len) {
-        return 1;
-    }
+    /* handle module indexes and such */
+    dconf = (void **) apr_pcalloc(r->pool, sizeof(void *) * (total_modules + DYNAMIC_MODULE_LIMIT));
 
-    r->filename = ap_getword(r->pool, (const char **)&data, '\n'); 
-    *argv0 = ap_getword(r->pool, (const char **)&data, '\n'); 
+    temp_core = (core_dir_config *)apr_palloc(r->pool, sizeof(core_module)); 
+    dconf[req->core_module_index] = (void *)temp_core;
 
-    r->uri = ap_getword(r->pool, (const char **)&data, '\n'); 
-    
-    environ = apr_pcalloc(r->pool, (j + 2) *sizeof(char *)); 
-    i = 0; 
-    for (i = 0; i < j; i++) { 
-        environ[i] = ap_getword(r->pool, (const char **)&data, '\n'); 
-    } 
-    *env = environ; 
-    r->args = ap_getword(r->pool, (const char **)&data, '\n'); 
-  
-    rc = read(fd, &i, sizeof(int)); 
-    if (rc != sizeof(int)) {
-        return 1;
+    if (req->have_suexec) {
+        dconf[req->suexec_module_index] = &req->suexec_cfg;
     }
-     
-    /* add 1, so that if i == 0, we still malloc something. */ 
 
-    dconf = (void **) apr_pcalloc(r->pool, sizeof(void *) * (total_modules + DYNAMIC_MODULE_LIMIT));
+    r->per_dir_config = (ap_conf_vector_t *)dconf; 
 
-    temp_core = (core_dir_config *)apr_palloc(r->pool, sizeof(core_module)); 
+    /* Read the filename, argv0, uri, and args */
+    r->filename = apr_pcalloc(r->pool, req->filename_len + 1);
+    *argv0 = apr_pcalloc(r->pool, req->argv0_len + 1);
+    r->uri = apr_pcalloc(r->pool, req->uri_len + 1);
+    if ((stat = sock_read(fd, r->filename, req->filename_len)) != APR_SUCCESS ||
+        (stat = sock_read(fd, *argv0, req->argv0_len)) != APR_SUCCESS ||
+        (stat = sock_read(fd, r->uri, req->uri_len)) != APR_SUCCESS) {
+        return stat;
+    }
 
-    dconf[i] = (void *)temp_core; 
+    r->args = apr_pcalloc(r->pool, req->args_len + 1); /* empty string if no args */
+    if (req->args_len) {
+        if ((stat = sock_read(fd, r->args, req->args_len)) != APR_SUCCESS) {
+            return stat;
+        }
+    }
 
-    if (suexec_mod) {
-        suexec_config_t *suexec_cfg = apr_pcalloc(r->pool, sizeof(*suexec_cfg));
+    /* read the environment variables */
+    environ = apr_pcalloc(r->pool, (req->env_count + 2) *sizeof(char *));
+    for (i = 0; i < req->env_count; i++) {
+        apr_size_t curlen;
 
-        rc = read(fd, &i, sizeof(int));
-        if (rc != sizeof(int)) {
-            return 1;
+        if ((stat = sock_read(fd, &curlen, sizeof(curlen))) != APR_SUCCESS) {
+            return stat;
         }
-        rc = read(fd, suexec_cfg, sizeof(*suexec_cfg));
-        if (rc != sizeof(*suexec_cfg)) {
-            return 1;
+        environ[i] = apr_pcalloc(r->pool, curlen + 1);
+        if ((stat = sock_read(fd, environ[i], curlen)) != APR_SUCCESS) {
+            return stat;
         }
-        dconf[i] = (void *)suexec_cfg;
+    }
+    *env = environ;
+
+    /* basic notes table to avoid segfaults */
+    r->notes = apr_table_make(r->pool, 1);
+
+    /* mod_userdir requires the mod_userdir_user note */
+    if (req->mod_userdir_user_len) {
+        user = apr_pcalloc(r->pool, req->mod_userdir_user_len + 1); /* last byte is '\0' */
+        stat = sock_read(fd, user, req->mod_userdir_user_len);
+        if (stat != APR_SUCCESS) {
+            return stat;
+        }
+        apr_table_set(r->notes, "mod_userdir_user", (const char *)user);
     }
 
-    r->per_dir_config = (ap_conf_vector_t *)dconf; 
 #if 0
 #ifdef RLIMIT_CPU 
-    read(fd, &j, sizeof(int)); 
+    sock_read(fd, &j, sizeof(int)); 
     if (j) { 
         temp_core->limit_cpu = (struct rlimit *)apr_palloc (sizeof(struct rlimit)); 
-        read(fd, temp_core->limit_cpu, sizeof(struct rlimit)); 
+        sock_read(fd, temp_core->limit_cpu, sizeof(struct rlimit)); 
     } 
     else { 
         temp_core->limit_cpu = NULL; 
     } 
 #endif 
 
 #if defined (RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined(RLIMIT_AS) 
-    read(fd, &j, sizeof(int)); 
+    sock_read(fd, &j, sizeof(int)); 
     if (j) { 
         temp_core->limit_mem = (struct rlimit *)apr_palloc(r->pool, sizeof(struct rlimit)); 
-        read(fd, temp_core->limit_mem, sizeof(struct rlimit)); 
+        sock_read(fd, temp_core->limit_mem, sizeof(struct rlimit)); 
     } 
     else { 
         temp_core->limit_mem = NULL; 
     } 
 #endif 
 
 #ifdef RLIMIT_NPROC 
-    read(fd, &j, sizeof(int)); 
+    sock_read(fd, &j, sizeof(int)); 
     if (j) { 
         temp_core->limit_nproc = (struct rlimit *)apr_palloc(r->pool, sizeof(struct rlimit)); 
-        read(fd, temp_core->limit_nproc, sizeof(struct rlimit)); 
+        sock_read(fd, temp_core->limit_nproc, sizeof(struct rlimit)); 
     } 
     else { 
         temp_core->limit_nproc = NULL; 
     } 
 #endif 
 #endif
 
-    /* basic notes table to avoid segfaults */
-    r->notes = apr_table_make(r->pool, 1);
-
-    /* mod_userdir requires the mod_userdir_user note */
-    rc = read(fd, &len, sizeof(len));
-    if ((rc == sizeof(len)) && len) {
-        data = apr_pcalloc(r->pool, len + 1); /* last byte is '\0' */
-        rc = read(fd, data, len);
-        if (rc != len) {
-            return 1;
-        }
-        apr_table_set(r->notes,"mod_userdir_user", (const char *)data);
-    }
-    return 0;
+    return APR_SUCCESS;
 } 
 
-
-
-static void send_req(int fd, request_rec *r, char *argv0, char **env, int req_type) 
+static apr_status_t send_req(int fd, request_rec *r, char *argv0, char **env, 
+                             int req_type) 
 { 
-    int len, r_type = req_type; 
-    int i = 0; 
-    char *data; 
+    int i;
+    const char *user;
     module *suexec_mod = ap_find_linked_module("mod_suexec.c");
-
-    data = apr_pstrcat(r->pool, r->filename, "\n", argv0, "\n", r->uri, "\n", 
-                     NULL); 
-
-    for (i =0; env[i]; i++) { 
+    cgid_req_t req = {0};
+    suexec_config_t *suexec_cfg;
+    apr_status_t stat;
+
+    req.req_type = req_type;
+    req.conn_id = r->connection->id;
+    req.core_module_index = core_module.module_index;
+    if (suexec_mod) {
+        req.have_suexec = 1;
+        req.suexec_module_index = suexec_mod->module_index;
+        suexec_cfg = ap_get_module_config(r->per_dir_config,
+                                          suexec_mod);
+        req.suexec_cfg = *suexec_cfg;
+    }
+    for (req.env_count = 0; env[req.env_count]; req.env_count++) {
         continue; 
-    } 
+    }
+    req.filename_len = strlen(r->filename);
+    req.argv0_len = strlen(argv0);
+    req.uri_len = strlen(r->uri);
+    req.args_len = r->args ? strlen(r->args) : 0;
+    user = (const char *)apr_table_get(r->notes, "mod_userdir_user");
+    if (user != NULL) {
+        req.mod_userdir_user_len = strlen(user);
+    }
 
-    /* Write the request type (SSI "exec cmd" or cgi). */
-    if (write(fd, &r_type, sizeof(int)) < 0) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r,
-                     "write to cgi daemon process");
+    /* Write the request header */
+    if ((stat = sock_write(fd, &req, sizeof(req))) != APR_SUCCESS) {
+        return stat;
     }
 
-    /* Write the number of entries in the environment. */
-    if (write(fd, &i, sizeof(int)) < 0) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, 
-                     "write to cgi daemon process"); 
-        }     
-
-    for (i = 0; env[i]; i++) { 
-        data = apr_pstrcat(r->pool, data, env[i], "\n", NULL); 
-    } 
-    data = apr_pstrcat(r->pool, data, r->args, NULL); 
-    len = strlen(data); 
-    /* Write the length of the concatenated env string. */
-    if (write(fd, &len, sizeof(int)) < 0) { 
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, 
-                     "write to cgi daemon process"); 
-    }
-    /* Write the concatted env string. */     
-    if (write(fd, data, len) < 0) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, 
-                     "write to cgi daemon process"); 
-    }
-    /* Write module_index id value. */     
-    if (write(fd, &core_module.module_index, sizeof(int)) < 0) { 
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, 
-                     "write to cgi daemon process"); 
-    }     
-    if (suexec_mod) {
-        suexec_config_t *suexec_cfg = ap_get_module_config(r->per_dir_config,
-                                                           suexec_mod);
+    /* Write filename, argv0, uri, and args */
+    if ((stat = sock_write(fd, r->filename, req.filename_len)) != APR_SUCCESS ||
+        (stat = sock_write(fd, argv0, req.argv0_len)) != APR_SUCCESS ||
+        (stat = sock_write(fd, r->uri, req.uri_len)) != APR_SUCCESS) {
+        return stat;
+    }
+    if (req.args_len) {
+        if ((stat = sock_write(fd, r->args, req.args_len)) != APR_SUCCESS) {
+            return stat;
+        }
+    }
+
+    /* write the environment variables */
+    for (i = 0; i < req.env_count; i++) {
+        apr_size_t curlen = strlen(env[i]);
+
+        if ((stat = sock_write(fd, &curlen, sizeof(curlen))) != APR_SUCCESS) {
+            return stat;
+        }
+            
+        if ((stat = sock_write(fd, env[i], curlen)) != APR_SUCCESS) {
+            return stat;
+        }
+    }
 
-        write(fd, &suexec_mod->module_index, sizeof(int));
-        write(fd, suexec_cfg, sizeof(*suexec_cfg));
+    /* send a minimal notes table */
+    if (user) {
+        if ((stat = sock_write(fd, user, req.mod_userdir_user_len)) != APR_SUCCESS) {
+            return stat;
+        }
     }
 
 #if 0
 #ifdef RLIMIT_CPU 
     if (conf->limit_cpu) { 
         len = 1; 
-        write(fd, &len, sizeof(int)); 
-        write(fd, conf->limit_cpu, sizeof(struct rlimit)); 
+        stat = sock_write(fd, &len, sizeof(int)); 
+        stat = sock_write(fd, conf->limit_cpu, sizeof(struct rlimit)); 
     } 
     else { 
         len = 0; 
-        write(fd, &len, sizeof(int)); 
+        stat = sock_write(fd, &len, sizeof(int)); 
     } 
 #endif 
 
 #if defined(RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined(RLIMIT_AS) 
     if (conf->limit_mem) { 
         len = 1; 
-        write(fd, &len, sizeof(int)); 
-        write(fd, conf->limit_mem, sizeof(struct rlimit)); 
+        stat = sock_write(fd, &len, sizeof(int)); 
+        stat = sock_write(fd, conf->limit_mem, sizeof(struct rlimit)); 
     } 
     else { 
         len = 0; 
-        write(fd, &len, sizeof(int)); 
+        stat = sock_write(fd, &len, sizeof(int)); 
     } 
 #endif 
   
 #ifdef RLIMIT_NPROC 
     if (conf->limit_nproc) { 
         len = 1; 
-        write(fd, &len, sizeof(int)); 
-        write(fd, conf->limit_nproc, sizeof(struct rlimit)); 
+        stat = sock_write(fd, &len, sizeof(int)); 
+        stat = sock_write(fd, conf->limit_nproc, sizeof(struct rlimit)); 
     } 
     else { 
         len = 0; 
-        write(fd, &len, sizeof(int)); 
+        stat = sock_write(fd, &len, sizeof(int)); 
     } 
 #endif
-#endif 
-   /* send a minimal notes table */
-   data  = (char *) apr_table_get(r->notes, "mod_userdir_user");
-   if (data != NULL) {
-       len = strlen(data);
-       write(fd, &len, sizeof(len));
-       write(fd, data, len);
-   }
-   else {
-       len = 0;
-       write(fd, &len, sizeof(len));
-   }
+#endif
+    return APR_SUCCESS;
 } 
 
 static void daemon_signal_handler(int sig)
 {
     if (sig == SIGHUP) {
         ++daemon_should_exit;
     }
 }
 
 static int cgid_server(void *data) 
 { 
     struct sockaddr_un unix_addr;
-    int sd, sd2, rc, req_type;
+    int sd, sd2, rc;
     mode_t omask;
     apr_socklen_t len;
     apr_pool_t *ptrans;
     server_rec *main_server = data;
     cgid_server_conf *sconf = ap_get_module_config(main_server->module_config,
                                                    &cgid_module); 
+    apr_hash_t *script_hash = apr_hash_make(pcgi);
 
     apr_pool_create(&ptrans, pcgi); 
 
     apr_signal(SIGCHLD, SIG_IGN); 
     apr_signal(SIGHUP, daemon_signal_handler);
 
