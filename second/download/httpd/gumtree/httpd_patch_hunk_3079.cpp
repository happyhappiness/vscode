      */
     lbmethod = ap_lookup_provider(PROXY_LBMETHOD, "byrequests", "0");
     if (!lbmethod) {
         return "Can't find 'byrequests' lb method";
     }
 
-    (*balancer)->name = uri;
-    (*balancer)->lbmethod = lbmethod;
     (*balancer)->workers = apr_array_make(p, 5, sizeof(proxy_worker *));
-    (*balancer)->updated = apr_time_now();
-    /* XXX Is this a right place to create mutex */
-#if APR_HAS_THREADS
-    if (apr_thread_mutex_create(&((*balancer)->mutex),
-                APR_THREAD_MUTEX_DEFAULT, p) != APR_SUCCESS) {
-        /* XXX: Do we need to log something here */
-        return "can not create thread mutex";
+    (*balancer)->gmutex = NULL;
+    (*balancer)->tmutex = NULL;
+    (*balancer)->lbmethod = lbmethod;
+
+    if (do_malloc)
+        bshared = ap_malloc(sizeof(proxy_balancer_shared));
+    else
+        bshared = apr_palloc(p, sizeof(proxy_balancer_shared));
+
+    memset(bshared, 0, sizeof(proxy_balancer_shared));
+
+    bshared->was_malloced = (do_malloc != 0);
+    PROXY_STRNCPY(bshared->lbpname, "byrequests");
+    if (PROXY_STRNCPY(bshared->name, uri) != APR_SUCCESS) {
+        return apr_psprintf(p, "balancer name (%s) too long", uri);
     }
-#endif
+    ap_pstr2_alnum(p, bshared->name + sizeof(BALANCER_PREFIX) - 1,
+                   &sname);
+    sname = apr_pstrcat(p, conf->id, "_", sname, NULL);
+    if (PROXY_STRNCPY(bshared->sname, sname) != APR_SUCCESS) {
+        return apr_psprintf(p, "balancer safe-name (%s) too long", sname);
+    }
+    bshared->hash.def = ap_proxy_hashfunc(bshared->name, PROXY_HASHFUNC_DEFAULT);
+    bshared->hash.fnv = ap_proxy_hashfunc(bshared->name, PROXY_HASHFUNC_FNV);
+    (*balancer)->hash = bshared->hash;
 
-    return NULL;
+    /* Retrieve a UUID and store the nonce for the lifetime of
+     * the process. */
+    apr_uuid_get(&uuid);
+    apr_uuid_format(nonce, &uuid);
+    if (PROXY_STRNCPY(bshared->nonce, nonce) != APR_SUCCESS) {
+        return apr_psprintf(p, "balancer nonce (%s) too long", nonce);
+    }
+
+    (*balancer)->s = bshared;
+    (*balancer)->sconf = conf;
+
+    return ap_proxy_update_balancer(p, *balancer, alias);
 }
 
-PROXY_DECLARE(proxy_worker *) ap_proxy_get_worker(apr_pool_t *p,
-                                                  proxy_server_conf *conf,
-                                                  const char *url)
+/*
+ * Create an already defined balancer and free up memory.
+ */
+PROXY_DECLARE(apr_status_t) ap_proxy_share_balancer(proxy_balancer *balancer,
+                                                    proxy_balancer_shared *shm,
+                                                    int i)
 {
-    proxy_worker *worker;
-    proxy_worker *max_worker = NULL;
-    int max_match = 0;
-    int url_length;
-    int min_match;
-    int worker_name_length;
-    const char *c;
-    char *url_copy;
-    int i;
-
-    c = ap_strchr_c(url, ':');
-    if (c == NULL || c[1] != '/' || c[2] != '/' || c[3] == '\0') {
-       return NULL;
-    }
+    proxy_balancer_method *lbmethod;
+    if (!shm || !balancer->s)
+        return APR_EINVAL;
 
-    url_copy = apr_pstrdup(p, url);
-    url_length = strlen(url);
+    memcpy(shm, balancer->s, sizeof(proxy_balancer_shared));
+    if (balancer->s->was_malloced)
+        free(balancer->s);
+    balancer->s = shm;
+    balancer->s->index = i;
+    /* the below should always succeed */
+    lbmethod = ap_lookup_provider(PROXY_LBMETHOD, balancer->s->lbpname, "0");
+    if (lbmethod)
+        balancer->lbmethod = lbmethod;
+    return APR_SUCCESS;
+}
 
+PROXY_DECLARE(apr_status_t) ap_proxy_initialize_balancer(proxy_balancer *balancer, server_rec *s, apr_pool_t *p)
+{
+    apr_status_t rv = APR_SUCCESS;
+    ap_slotmem_provider_t *storage = balancer->storage;
+    apr_size_t size;
+    unsigned int num;
+
+    if (!storage) {
+        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, APLOGNO(00918)
+                     "no provider for %s", balancer->s->name);
+        return APR_EGENERAL;
+    }
     /*
-     * We need to find the start of the path and
-     * therefore we know the length of the scheme://hostname/
-     * part to we can force-lowercase everything up to
-     * the start of the path.
+     * for each balancer we need to init the global
+     * mutex and then attach to the shared worker shm
      */
-    c = ap_strchr_c(c+3, '/');
-    if (c) {
-        char *pathstart;
-        pathstart = url_copy + (c - url);
-        *pathstart = '\0';
-        ap_str_tolower(url_copy);
-        min_match = strlen(url_copy);
-        *pathstart = '/';
+    if (!balancer->gmutex) {
+        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, APLOGNO(00919)
+                     "no mutex %s", balancer->s->name);
+        return APR_EGENERAL;
     }
-    else {
-        ap_str_tolower(url_copy);
-        min_match = strlen(url_copy);
+
+    /* Re-open the mutex for the child. */
+    rv = apr_global_mutex_child_init(&(balancer->gmutex),
+                                     apr_global_mutex_lockfile(balancer->gmutex),
+                                     p);
+    if (rv != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(00920)
+                     "Failed to reopen mutex %s in child",
+                     balancer->s->name);
+        return rv;
     }
 
-    worker = (proxy_worker *)conf->workers->elts;
+    /* now attach */
+    storage->attach(&(balancer->wslot), balancer->s->sname, &size, &num, p);
+    if (!balancer->wslot) {
+        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, APLOGNO(00921) "slotmem_attach failed");
+        return APR_EGENERAL;
+    }
+    if (balancer->lbmethod && balancer->lbmethod->reset)
+        balancer->lbmethod->reset(balancer, s);
 
-    /*
-     * Do a "longest match" on the worker name to find the worker that
-     * fits best to the URL, but keep in mind that we must have at least
-     * a minimum matching of length min_match such that
-     * scheme://hostname[:port] matches between worker and url.
-     */
-    for (i = 0; i < conf->workers->nelts; i++) {
-        if ( ((worker_name_length = strlen(worker->name)) <= url_length)
-           && (worker_name_length >= min_match)
-           && (worker_name_length > max_match)
-           && (strncmp(url_copy, worker->name, worker_name_length) == 0) ) {
-            max_worker = worker;
-            max_match = worker_name_length;
+    if (balancer->tmutex == NULL) {
+        rv = apr_thread_mutex_create(&(balancer->tmutex), APR_THREAD_MUTEX_DEFAULT, p);
+        if (rv != APR_SUCCESS) {
+            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, APLOGNO(00922)
+                         "can not create balancer thread mutex");
+            return rv;
         }
-        worker++;
     }
-    return max_worker;
+    return APR_SUCCESS;
 }
 
-#if APR_HAS_THREADS
+/*
+ * CONNECTION related...
+ */
+
 static apr_status_t conn_pool_cleanup(void *theworker)
 {
     proxy_worker *worker = (proxy_worker *)theworker;
     if (worker->cp->res) {
         worker->cp->pool = NULL;
     }
     return APR_SUCCESS;
 }
-#endif
 
 static void init_conn_pool(apr_pool_t *p, proxy_worker *worker)
 {
     apr_pool_t *pool;
     proxy_conn_pool *cp;
 
