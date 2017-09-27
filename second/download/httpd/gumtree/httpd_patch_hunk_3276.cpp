      */
     rv = apr_socket_opt_set(csd, APR_TCP_NODELAY, 1);
     if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
         /* expected cause is that the client disconnected already,
          * hence the debug level
          */
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rv, c,
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rv, c, APLOGNO(00139)
                       "apr_socket_opt_set(APR_TCP_NODELAY)");
     }
 
     /* The core filter requires the timeout mode to be set, which
      * incidentally sets the socket to be nonblocking.  If this
      * is not initialized correctly, Linux - for example - will
      * be initially blocking, while Solaris will be non blocking
      * and any initial read will fail.
      */
     rv = apr_socket_timeout_set(csd, c->base_server->timeout);
     if (rv != APR_SUCCESS) {
         /* expected cause is that the client disconnected already */
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rv, c,
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rv, c, APLOGNO(00140)
                       "apr_socket_timeout_set");
     }
 
     net->c = c;
     net->in_ctx = NULL;
     net->out_ctx = NULL;
     net->client_socket = csd;
 
-    ap_set_module_config(net->c->conn_config, &core_module, csd);
+    ap_set_core_module_config(net->c->conn_config, csd);
     ap_add_input_filter_handle(ap_core_input_filter_handle, net, NULL, net->c);
     ap_add_output_filter_handle(ap_core_output_filter_handle, net, NULL, net->c);
     return DONE;
 }
 
+AP_DECLARE(int) ap_state_query(int query)
+{
+    switch (query) {
+    case AP_SQ_MAIN_STATE:
+        return ap_main_state;
+    case AP_SQ_RUN_MODE:
+        return ap_run_mode;
+    case AP_SQ_CONFIG_GEN:
+        return ap_config_generation;
+    default:
+        return AP_SQ_NOT_SUPPORTED;
+    }
+}
+
+static apr_random_t *rng = NULL;
+#if APR_HAS_THREADS
+static apr_thread_mutex_t *rng_mutex = NULL;
+#endif
+
+static void core_child_init(apr_pool_t *pchild, server_rec *s)
+{
+    apr_proc_t proc;
+#if APR_HAS_THREADS
+    int threaded_mpm;
+    if (ap_mpm_query(AP_MPMQ_IS_THREADED, &threaded_mpm) == APR_SUCCESS
+        && threaded_mpm)
+    {
+        apr_thread_mutex_create(&rng_mutex, APR_THREAD_MUTEX_DEFAULT, pchild);
+    }
+#endif
+    /* The MPMs use plain fork() and not apr_proc_fork(), so we have to call
+     * apr_random_after_fork() manually in the child
+     */
+    proc.pid = getpid();
+    apr_random_after_fork(&proc);
+}
+
+AP_CORE_DECLARE(void) ap_random_parent_after_fork(void)
+{
+    /*
+     * To ensure that the RNG state in the parent changes after the fork, we
+     * pull some data from the RNG and discard it. This ensures that the RNG
+     * states in the children are different even after the pid wraps around.
+     * As we only use apr_random for insecure random bytes, pulling 2 bytes
+     * should be enough.
+     * XXX: APR should probably have some dedicated API to do this, but it
+     * XXX: currently doesn't.
+     */
+    apr_uint16_t data;
+    apr_random_insecure_bytes(rng, &data, sizeof(data));
+}
+
+AP_CORE_DECLARE(void) ap_init_rng(apr_pool_t *p)
+{
+    unsigned char seed[8];
+    apr_status_t rv;
+    rng = apr_random_standard_new(p);
+    do {
+        rv = apr_generate_random_bytes(seed, sizeof(seed));
+        if (rv != APR_SUCCESS)
+            goto error;
+        apr_random_add_entropy(rng, seed, sizeof(seed));
+        rv = apr_random_insecure_ready(rng);
+    } while (rv == APR_ENOTENOUGHENTROPY);
+    if (rv == APR_SUCCESS)
+        return;
+error:
+    ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL, APLOGNO(00141)
+                 "Could not initialize random number generator");
+    exit(1);
+}
+
+AP_DECLARE(void) ap_random_insecure_bytes(void *buf, apr_size_t size)
+{
+#if APR_HAS_THREADS
+    if (rng_mutex)
+        apr_thread_mutex_lock(rng_mutex);
+#endif
+    /* apr_random_insecure_bytes can only fail with APR_ENOTENOUGHENTROPY,
+     * and we have ruled that out during initialization. Therefore we don't
+     * need to check the return code.
+     */
+    apr_random_insecure_bytes(rng, buf, size);
+#if APR_HAS_THREADS
+    if (rng_mutex)
+        apr_thread_mutex_unlock(rng_mutex);
+#endif
+}
+
+/*
+ * Finding a random number in a range.
+ *      n' = a + n(b-a+1)/(M+1)
+ * where:
+ *      n' = random number in range
+ *      a  = low end of range
+ *      b  = high end of range
+ *      n  = random number of 0..M
+ *      M  = maxint
+ * Algorithm 'borrowed' from PHP's rand() function.
+ */
+#define RAND_RANGE(__n, __min, __max, __tmax) \
+(__n) = (__min) + (long) ((double) ((__max) - (__min) + 1.0) * ((__n) / ((__tmax) + 1.0)))
+AP_DECLARE(apr_uint32_t) ap_random_pick(apr_uint32_t min, apr_uint32_t max)
+{
+    apr_uint32_t number;
+    if (max < 16384) {
+        apr_uint16_t num16;
+        ap_random_insecure_bytes(&num16, sizeof(num16));
+        RAND_RANGE(num16, min, max, APR_UINT16_MAX);
+        number = num16;
+    }
+    else {
+        ap_random_insecure_bytes(&number, sizeof(number));
+        RAND_RANGE(number, min, max, APR_UINT32_MAX);
+    }
+    return number;
+}
+
+static apr_status_t core_insert_network_bucket(conn_rec *c,
+                                               apr_bucket_brigade *bb,
+                                               apr_socket_t *socket)
+{
+    apr_bucket *e = apr_bucket_socket_create(socket, c->bucket_alloc);
+    APR_BRIGADE_INSERT_TAIL(bb, e);
+    return APR_SUCCESS;
+}
+
+static void core_dump_config(apr_pool_t *p, server_rec *s)
+{
+    core_server_config *sconf = ap_get_core_module_config(s->module_config);
+    apr_file_t *out = NULL;
+    const char *tmp;
+    const char **defines;
+    int i;
+    if (!ap_exists_config_define("DUMP_RUN_CFG"))
+        return;
+
+    apr_file_open_stdout(&out, p);
+    apr_file_printf(out, "ServerRoot: \"%s\"\n", ap_server_root);
+    tmp = ap_server_root_relative(p, sconf->ap_document_root);
+    apr_file_printf(out, "Main DocumentRoot: \"%s\"\n", tmp);
+    if (s->error_fname[0] != '|' && strcmp(s->error_fname, "syslog") != 0)
+        tmp = ap_server_root_relative(p, s->error_fname);
+    else
+        tmp = s->error_fname;
+    apr_file_printf(out, "Main ErrorLog: \"%s\"\n", tmp);
+    if (ap_scoreboard_fname) {
+        tmp = ap_server_root_relative(p, ap_scoreboard_fname);
+        apr_file_printf(out, "ScoreBoardFile: \"%s\"\n", tmp);
+    }
+    ap_dump_mutexes(p, s, out);
+    ap_mpm_dump_pidfile(p, out);
+
+    defines = (const char **)ap_server_config_defines->elts;
+    for (i = 0; i < ap_server_config_defines->nelts; i++) {
+        const char *name = defines[i];
+        const char *val = NULL;
+        if (server_config_defined_vars)
+           val = apr_table_get(server_config_defined_vars, name);
+        if (val)
+            apr_file_printf(out, "Define: %s=%s\n", name, val);
+        else
+            apr_file_printf(out, "Define: %s\n", name);
+    }
+}
+
 static void register_hooks(apr_pool_t *p)
 {
+    errorlog_hash = apr_hash_make(p);
+    ap_register_log_hooks(p);
+    ap_register_config_hooks(p);
+    ap_expr_init(p);
+
     /* create_connection and pre_connection should always be hooked
      * APR_HOOK_REALLY_LAST by core to give other modules the opportunity
-     * to install alternate network transports and stop other functions 
+     * to install alternate network transports and stop other functions
      * from being run.
      */
     ap_hook_create_connection(core_create_conn, NULL, NULL,
                               APR_HOOK_REALLY_LAST);
     ap_hook_pre_connection(core_pre_connection, NULL, NULL,
                            APR_HOOK_REALLY_LAST);
 
     ap_hook_pre_config(core_pre_config, NULL, NULL, APR_HOOK_REALLY_FIRST);
     ap_hook_post_config(core_post_config,NULL,NULL,APR_HOOK_REALLY_FIRST);
+    ap_hook_check_config(core_check_config,NULL,NULL,APR_HOOK_FIRST);
+    ap_hook_test_config(core_dump_config,NULL,NULL,APR_HOOK_FIRST);
     ap_hook_translate_name(ap_core_translate,NULL,NULL,APR_HOOK_REALLY_LAST);
     ap_hook_map_to_storage(core_map_to_storage,NULL,NULL,APR_HOOK_REALLY_LAST);
     ap_hook_open_logs(ap_open_logs,NULL,NULL,APR_HOOK_REALLY_FIRST);
+    ap_hook_child_init(core_child_init,NULL,NULL,APR_HOOK_REALLY_FIRST);
     ap_hook_child_init(ap_logs_child_init,NULL,NULL,APR_HOOK_MIDDLE);
     ap_hook_handler(default_handler,NULL,NULL,APR_HOOK_REALLY_LAST);
     /* FIXME: I suspect we can eliminate the need for these do_nothings - Ben */
     ap_hook_type_checker(do_nothing,NULL,NULL,APR_HOOK_REALLY_LAST);
     ap_hook_fixups(core_override_type,NULL,NULL,APR_HOOK_REALLY_FIRST);
     ap_hook_create_request(core_create_req, NULL, NULL, APR_HOOK_MIDDLE);
     APR_OPTIONAL_HOOK(proxy, create_req, core_create_proxy_req, NULL, NULL,
                       APR_HOOK_MIDDLE);
     ap_hook_pre_mpm(ap_create_scoreboard, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_child_status(ap_core_child_status, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_insert_network_bucket(core_insert_network_bucket, NULL, NULL,
+                                  APR_HOOK_REALLY_LAST);
 
     /* register the core's insert_filter hook and register core-provided
      * filters
      */
     ap_hook_insert_filter(core_insert_filter, NULL, NULL, APR_HOOK_MIDDLE);
 
