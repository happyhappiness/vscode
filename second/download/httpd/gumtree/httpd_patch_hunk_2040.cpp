     /* XXX: note that mod_proxy calls this "ttl" (time to live) */
     AP_INIT_TAKE1("DBDExptime", dbd_param, (void*)cmd_exp, RSRC_CONF,
                   "Keepalive time for idle connections"),
 #endif
     {NULL}
 };
-static void *dbd_merge(apr_pool_t *pool, void *BASE, void *ADD) {
-    svr_cfg *base = (svr_cfg*) BASE;
-    svr_cfg *add = (svr_cfg*) ADD;
-    svr_cfg *cfg = apr_pcalloc(pool, sizeof(svr_cfg));
-    cfg->name = (add->name != no_dbdriver) ? add->name : base->name;
-    cfg->params = strcmp(add->params, "") ? add->params : base->params;
-    cfg->persist = (add->persist == -1) ? base->persist : add->persist;
-#if APR_HAS_THREADS
-    cfg->nmin = (add->set&NMIN_SET) ? add->nmin : base->nmin;
-    cfg->nkeep = (add->set&NKEEP_SET) ? add->nkeep : base->nkeep;
-    cfg->nmax = (add->set&NMAX_SET) ? add->nmax : base->nmax;
-    cfg->exptime = (add->set&EXPTIME_SET) ? add->exptime : base->exptime;
-#endif
-    cfg->set = add->set | base->set;
-    cfg->prepared = (add->prepared != NULL) ? add->prepared : base->prepared;
-    return (void*) cfg;
+
+static int dbd_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
+                          apr_pool_t *ptemp)
+{
+   config_pool = pconf;
+   group_list = NULL;
+   return OK;
 }
-/* A default nmin of >0 will help with generating meaningful
- * startup error messages if the database is down.
- */
-#define DEFAULT_NMIN 1
-#define DEFAULT_NKEEP 2
-#define DEFAULT_NMAX 10
-#define DEFAULT_EXPTIME 300
-static void *dbd_cfg(apr_pool_t *p, server_rec *x)
+
+DBD_DECLARE_NONSTD(void) ap_dbd_prepare(server_rec *s, const char *query,
+                                        const char *label)
+{
+    svr_cfg *svr;
+
+    svr = ap_get_module_config(s->module_config, &dbd_module);
+    if (!svr) {
+         /* some modules may call from within config directive handlers, and
+          * if these are called in a server context that contains no mod_dbd
+          * config directives, then we have to create our own server config
+          */
+         svr = create_dbd_config(config_pool, s);
+         ap_set_module_config(s->module_config, &dbd_module, svr);
+    }
+
+    if (apr_hash_get(svr->cfg->queries, label, APR_HASH_KEY_STRING)
+        && strcmp(query, "")) {
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                     "conflicting SQL statements with label %s", label);
+    }
+
+    apr_hash_set(svr->cfg->queries, label, APR_HASH_KEY_STRING, query);
+}
+
+typedef struct {
+    const char *label, *query;
+} dbd_query_t;
+
+static int dbd_post_config(apr_pool_t *pconf, apr_pool_t *plog,
+                           apr_pool_t *ptemp, server_rec *s)
 {
-    svr_cfg *svr = (svr_cfg*) apr_pcalloc(p, sizeof(svr_cfg));
-    svr->params = ""; /* don't risk segfault on misconfiguration */
-    svr->name = no_dbdriver; /* to generate meaningful error messages */
-    svr->persist = -1;
-#if APR_HAS_THREADS
-    svr->nmin = DEFAULT_NMIN;
-    svr->nkeep = DEFAULT_NKEEP;
-    svr->nmax = DEFAULT_NMAX;
-    svr->exptime = DEFAULT_EXPTIME;
+    server_rec *sp;
+    apr_array_header_t *add_queries = apr_array_make(ptemp, 10,
+                                                     sizeof(dbd_query_t));
+
+    for (sp = s; sp; sp = sp->next) {
+        svr_cfg *svr = ap_get_module_config(sp->module_config, &dbd_module);
+        dbd_cfg_t *cfg = svr->cfg;
+        apr_hash_index_t *hi_first = apr_hash_first(ptemp, cfg->queries);
+        dbd_group_t *group;
+
+        /* dbd_setup in 2.2.3 and under was causing spurious error messages
+         * when dbd isn't configured.  We can stop that with a quick check here
+         * together with a similar check in ap_dbd_open (where being
+         * unconfigured is a genuine error that must be reported).
+         */
+        if (cfg->name == no_dbdriver || !cfg->persist) {
+            continue;
+        }
+
+        for (group = group_list; group; group = group->next) {
+            dbd_cfg_t *group_cfg = group->cfg;
+            apr_hash_index_t *hi;
+            int group_ok = 1;
+
+            if (strcmp(cfg->name, group_cfg->name)
+                || strcmp(cfg->params, group_cfg->params)) {
+                continue;
+            }
+
+#if APR_HAS_THREADS
+            if (cfg->nmin != group_cfg->nmin
+                || cfg->nkeep != group_cfg->nkeep
+                || cfg->nmax != group_cfg->nmax
+                || cfg->exptime != group_cfg->exptime) {
+                continue;
+            }
 #endif
-    return svr;
+
+            add_queries->nelts = 0;
+
+            for (hi = hi_first; hi; hi = apr_hash_next(hi)) {
+                const char *label, *query;
+                const char *group_query;
+
+                apr_hash_this(hi, (void*) &label, NULL, (void*) &query);
+
+                group_query = apr_hash_get(group_cfg->queries, label,
+                                           APR_HASH_KEY_STRING);
+
+                if (!group_query) {
+                    dbd_query_t *add_query = apr_array_push(add_queries);
+
+                    add_query->label = label;
+                    add_query->query = query;
+                }
+                else if (strcmp(query, group_query)) {
+                    group_ok = 0;
+                    break;
+                }
+            }
+
+            if (group_ok) {
+                int i;
+
+                for (i = 0; i < add_queries->nelts; ++i) {
+                    dbd_query_t *add_query = ((dbd_query_t*) add_queries->elts)
+                                             + i;
+
+                    apr_hash_set(group_cfg->queries, add_query->label,
+                                 APR_HASH_KEY_STRING, add_query->query);
+                }
+
+                svr->group = group;
+                break;
+            }
+        }
+
+        if (!svr->group) {
+            svr->group = group = apr_pcalloc(pconf, sizeof(dbd_group_t));
+
+            group->cfg = cfg;
+
+            group->next = group_list;
+            group_list = group;
+        }
+    }
+
+    return OK;
 }
-static apr_status_t dbd_prepared_init(apr_pool_t *pool, svr_cfg *svr,
-                                      ap_dbd_t *dbd)
+
+static apr_status_t dbd_prepared_init(apr_pool_t *pool, dbd_cfg_t *cfg,
+                                      ap_dbd_t *rec)
 {
-    dbd_prepared *p;
-    apr_status_t ret = APR_SUCCESS;
-    apr_dbd_prepared_t *stmt;
-    dbd->prepared = apr_hash_make(pool);
+    apr_hash_index_t *hi;
+    apr_status_t rv = APR_SUCCESS;
+
+    rec->prepared = apr_hash_make(pool);
+
+    for (hi = apr_hash_first(pool, cfg->queries); hi;
+         hi = apr_hash_next(hi)) {
+        const char *label, *query;
+        apr_dbd_prepared_t *stmt;
+
+        apr_hash_this(hi, (void*) &label, NULL, (void*) &query);
+
+        if (!strcmp(query, "")) {
+            continue;
+        }
 
-    for (p = svr->prepared; p; p = p->next) {
         stmt = NULL;
-        if (apr_dbd_prepare(dbd->driver, pool, dbd->handle, p->query,
-                            p->label, &stmt) == 0) {
-            apr_hash_set(dbd->prepared, p->label, APR_HASH_KEY_STRING, stmt);
+        if (apr_dbd_prepare(rec->driver, pool, rec->handle, query,
+                            label, &stmt)) {
+            rv = APR_EGENERAL;
         }
         else {
-            ret = APR_EGENERAL;
+            apr_hash_set(rec->prepared, label, APR_HASH_KEY_STRING, stmt);
         }
     }
-    return ret;
+
+    return rv;
 }
-/************ svr cfg: manage db connection pool ****************/
+
+static apr_status_t dbd_close(void *data)
+{
+    ap_dbd_t *rec = data;
+
+    return apr_dbd_close(rec->driver, rec->handle);
+}
+
+#if APR_HAS_THREADS
+static apr_status_t dbd_destruct(void *data, void *params, apr_pool_t *pool)
+{
+    dbd_group_t *group = params;
+
+    if (!group->destroyed) {
+        ap_dbd_t *rec = data;
+
+        apr_pool_destroy(rec->pool);
+    }
+
+    return APR_SUCCESS;
+}
+#endif
+
 /* an apr_reslist_constructor for SQL connections
  * Also use this for opening in non-reslist modes, since it gives
  * us all the error-handling in one place.
  */
-static apr_status_t dbd_construct(void **db, void *params, apr_pool_t *pool)
+static apr_status_t dbd_construct(void **data_ptr,
+                                  void *params, apr_pool_t *pool)
 {
-    svr_cfg *svr = (svr_cfg*) params;
-    ap_dbd_t *rec = apr_pcalloc(pool, sizeof(ap_dbd_t));
+    dbd_group_t *group = params;
+    dbd_cfg_t *cfg = group->cfg;
+    apr_pool_t *rec_pool, *prepared_pool;
+    ap_dbd_t *rec;
     apr_status_t rv;
 
-    /* this pool is mostly so dbd_close can destroy the prepared stmts */
-    rv = apr_pool_create(&rec->pool, pool);
+    rv = apr_pool_create(&rec_pool, pool);
     if (rv != APR_SUCCESS) {
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, pool,
-                      "DBD: Failed to create memory pool");
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, cfg->server,
+                     "DBD: Failed to create memory pool");
+        return rv;
     }
 
-/* The driver is loaded at config time now, so this just checks a hash.
- * If that changes, the driver DSO could be registered to unload against
- * our pool, which is probably not what we want.  Error checking isn't
- * necessary now, but in case that changes in the future ...
- */
-    rv = apr_dbd_get_driver(rec->pool, svr->name, &rec->driver);
-    switch (rv) {
-    case APR_ENOTIMPL:
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
-                      "DBD: driver for %s not available", svr->name);
-        return rv;
-    case APR_EDSOOPEN:
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
-                      "DBD: can't find driver for %s", svr->name);
-        return rv;
-    case APR_ESYMNOTFOUND:
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
-                      "DBD: driver for %s is invalid or corrupted", svr->name);
-        return rv;
-    default:
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
-                      "DBD: mod_dbd not compatible with apr in get_driver");
+    rec = apr_pcalloc(rec_pool, sizeof(ap_dbd_t));
+
+    rec->pool = rec_pool;
+
+    /* The driver is loaded at config time now, so this just checks a hash.
+     * If that changes, the driver DSO could be registered to unload against
+     * our pool, which is probably not what we want.  Error checking isn't
+     * necessary now, but in case that changes in the future ...
+     */
+    rv = apr_dbd_get_driver(rec->pool, cfg->name, &rec->driver);
+    if (rv != APR_SUCCESS) {
+        switch (rv) {
+        case APR_ENOTIMPL:
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
+                         "DBD: driver for %s not available", cfg->name);
+            break;
+        case APR_EDSOOPEN:
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
+                         "DBD: can't find driver for %s", cfg->name);
+            break;
+        case APR_ESYMNOTFOUND:
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
+                         "DBD: driver for %s is invalid or corrupted",
+                         cfg->name);
+            break;
+        default:
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
+                         "DBD: mod_dbd not compatible with APR in get_driver");
+            break;
+        }
+
+        apr_pool_destroy(rec->pool);
         return rv;
-    case APR_SUCCESS:
-        break;
     }
 
-    rv = apr_dbd_open(rec->driver, rec->pool, svr->params, &rec->handle);
-    switch (rv) {
-    case APR_EGENERAL:
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
-                      "DBD: Can't connect to %s", svr->name);
+    rv = apr_dbd_open(rec->driver, rec->pool, cfg->params, &rec->handle);
+    if (rv != APR_SUCCESS) {
+        switch (rv) {
+        case APR_EGENERAL:
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
+                         "DBD: Can't connect to %s", cfg->name);
+            break;
+        default:
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
+                         "DBD: mod_dbd not compatible with APR in open");
+            break;
+        }
+
+        apr_pool_destroy(rec->pool);
         return rv;
-    default:
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
-                      "DBD: mod_dbd not compatible with apr in open");
+    }
+
+    apr_pool_cleanup_register(rec->pool, rec, dbd_close,
+                              apr_pool_cleanup_null);
+
+    /* we use a sub-pool for the prepared statements for each connection so
+     * that they will be cleaned up first, before the connection is closed
+     */
+    rv = apr_pool_create(&prepared_pool, rec->pool);
+    if (rv != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, cfg->server,
+                     "DBD: Failed to create memory pool");
+
+        apr_pool_destroy(rec->pool);
         return rv;
-    case APR_SUCCESS:
-        break;
     }
-    *db = rec;
-    rv = dbd_prepared_init(rec->pool, svr, rec);
+
+    rv = dbd_prepared_init(prepared_pool, cfg, rec);
     if (rv != APR_SUCCESS) {
         const char *errmsg = apr_dbd_error(rec->driver, rec->handle, rv);
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
-                      "DBD: failed to initialise prepared SQL statements: %s",
-                      (errmsg ? errmsg : "[???]"));
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
+                     "DBD: failed to prepare SQL statements: %s",
+                     (errmsg ? errmsg : "[???]"));
+
+        apr_pool_destroy(rec->pool);
+        return rv;
     }
-    return rv;
-}
-static apr_status_t dbd_close(void *CONN)
-{
-    ap_dbd_t *conn = CONN;
-    apr_status_t rv = apr_dbd_close(conn->driver, conn->handle);
-    apr_pool_destroy(conn->pool);
-    return rv;
+
+    *data_ptr = rec;
+
+    return APR_SUCCESS;
 }
+
 #if APR_HAS_THREADS
-static apr_status_t dbd_destruct(void *sql, void *params, apr_pool_t *pool)
+static apr_status_t dbd_destroy(void *data)
 {
-    return dbd_close(sql);
+    dbd_group_t *group = data;
+
+    group->destroyed = 1;
+
+    return APR_SUCCESS;
 }
 
-static apr_status_t dbd_setup(apr_pool_t *pool, svr_cfg *svr)
+static apr_status_t dbd_setup(server_rec *s, dbd_group_t *group)
 {
+    dbd_cfg_t *cfg = group->cfg;
     apr_status_t rv;
 
-    /* create a pool just for the reslist from a process-lifetime pool;
-     * that pool (s->process->pool in the dbd_setup_lock case,
-     * whatever was passed to ap_run_child_init in the dbd_setup_init case)
-     * will be shared with other threads doing other non-mod_dbd things
-     * so we can't use it for the reslist directly
+    /* We create the reslist using a sub-pool of the pool passed to our
+     * child_init hook.  No other threads can be here because we're
+     * either in the child_init phase or dbd_setup_lock() acquired our mutex.
+     * No other threads will use this sub-pool after this, except via
+     * reslist calls, which have an internal mutex.
+     *
+     * We need to short-circuit the cleanup registered internally by
+     * apr_reslist_create().  We do this by registering dbd_destroy()
+     * as a cleanup afterwards, so that it will run before the reslist's
+     * internal cleanup.
+     *
+     * If we didn't do this, then we could free memory twice when the pool
+     * was destroyed.  When apr_pool_destroy() runs, it first destroys all
+     * all the per-connection sub-pools created in dbd_construct(), and
+     * then it runs the reslist's cleanup.  The cleanup calls dbd_destruct()
+     * on each resource, which would then attempt to destroy the sub-pools
+     * a second time.
      */
-    rv = apr_pool_create(&svr->pool, pool);
+    rv = apr_reslist_create(&group->reslist,
+                            cfg->nmin, cfg->nkeep, cfg->nmax,
+                            apr_time_from_sec(cfg->exptime),
+                            dbd_construct, dbd_destruct, group,
+                            group->pool);
     if (rv != APR_SUCCESS) {
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, pool,
-                      "DBD: Failed to create reslist memory pool");
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
+                     "DBD: failed to initialise");
         return rv;
     }
 
-    rv = apr_reslist_create(&svr->dbpool, svr->nmin, svr->nkeep, svr->nmax,
-                            apr_time_from_sec(svr->exptime),
-                            dbd_construct, dbd_destruct, svr, svr->pool);
-    if (rv == APR_SUCCESS) {
-        apr_pool_cleanup_register(svr->pool, svr->dbpool,
-                                  (void*)apr_reslist_destroy,
-                                  apr_pool_cleanup_null);
-    }
-    else {
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, svr->pool,
-                      "DBD: failed to initialise");
-        apr_pool_destroy(svr->pool);
-        svr->pool = NULL;
-    }
+    apr_pool_cleanup_register(group->pool, group, dbd_destroy,
+                              apr_pool_cleanup_null);
 
-    return rv;
+    return APR_SUCCESS;
 }
+#endif
+
 static apr_status_t dbd_setup_init(apr_pool_t *pool, server_rec *s)
 {
-    svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
-    apr_status_t rv;
+    dbd_group_t *group;
+    apr_status_t rv = APR_SUCCESS;
 
-    /* dbd_setup in 2.2.3 and under was causing spurious error messages
-     * when dbd isn't configured.  We can stop that with a quick check here
-     * together with a similar check in ap_dbd_open (where being
-     * unconfigured is a genuine error that must be reported).
-     */
-    if (svr->name == no_dbdriver) {
-        return APR_SUCCESS;
-    }
+    for (group = group_list; group; group = group->next) {
+        apr_status_t rv2;
 
-    if (!svr->persist) {
-        return APR_SUCCESS;
-    }
+        rv2 = apr_pool_create(&group->pool, pool);
+        if (rv2 != APR_SUCCESS) {
+            ap_log_error(APLOG_MARK, APLOG_CRIT, rv2, s,
+                         "DBD: Failed to create reslist cleanup memory pool");
+            return rv2;
+        }
 
-    rv = dbd_setup(pool, svr);
-    if (rv == APR_SUCCESS) {
-        return rv;
-    }
+#if APR_HAS_THREADS
+        rv2 = dbd_setup(s, group);
+        if (rv2 == APR_SUCCESS) {
+            continue;
+        }
+        else if (rv == APR_SUCCESS) {
+            rv = rv2;
+        }
 
-    /* we failed, so create a mutex so that subsequent competing callers
-     * to ap_dbd_open can serialize themselves while they retry
-     */
-    rv = apr_thread_mutex_create(&svr->mutex, APR_THREAD_MUTEX_DEFAULT, pool);
-    if (rv != APR_SUCCESS) {
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, pool,
-                      "DBD: Failed to create thread mutex");
+        /* we failed, so create a mutex so that subsequent competing callers
+         * to ap_dbd_open can serialize themselves while they retry
+         */
+        rv2 = apr_thread_mutex_create(&group->mutex,
+                                      APR_THREAD_MUTEX_DEFAULT, pool);
+        if (rv2 != APR_SUCCESS) {
+             ap_log_error(APLOG_MARK, APLOG_CRIT, rv2, s,
+                          "DBD: Failed to create thread mutex");
+             return rv2;
+        }
+#endif
     }
+
     return rv;
 }
-static apr_status_t dbd_setup_lock(apr_pool_t *pool, server_rec *s)
+
+#if APR_HAS_THREADS
+static apr_status_t dbd_setup_lock(server_rec *s, dbd_group_t *group)
 {
-    svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
-    apr_status_t rv, rv2 = APR_SUCCESS;
+    apr_status_t rv = APR_SUCCESS, rv2;
 
     /* several threads could be here at the same time, all trying to
      * initialize the reslist because dbd_setup_init failed to do so
      */
-    if (!svr->mutex) {
+    if (!group->mutex) {
         /* we already logged an error when the mutex couldn't be created */
         return APR_EGENERAL;
     }
 
-    rv = apr_thread_mutex_lock(svr->mutex);
-    if (rv != APR_SUCCESS) {
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, pool,
-                      "DBD: Failed to acquire thread mutex");
-        return rv;
-    }
-
-    if (!svr->dbpool) {
-        rv2 = dbd_setup(s->process->pool, svr);
-    }
-
-    rv = apr_thread_mutex_unlock(svr->mutex);
-    if (rv != APR_SUCCESS) {
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, pool,
-                      "DBD: Failed to release thread mutex");
-        if (rv2 == APR_SUCCESS) {
-            rv2 = rv;
+    rv2 = apr_thread_mutex_lock(group->mutex);
+    if (rv2 != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv2, s,
+                     "DBD: Failed to acquire thread mutex");
+        return rv2;
+    }
+
+    if (!group->reslist) {
+        rv = dbd_setup(s, group);
+    }
+
+    rv2 = apr_thread_mutex_unlock(group->mutex);
+    if (rv2 != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv2, s,
+                     "DBD: Failed to release thread mutex");
+        if (rv == APR_SUCCESS) {
+            rv = rv2;
         }
     }
-    return rv2;
+
+    return rv;
 }
 #endif
 
-
 /* Functions we export for modules to use:
         - open acquires a connection from the pool (opens one if necessary)
         - close releases it back in to the pool
 */
-DBD_DECLARE_NONSTD(void) ap_dbd_close(server_rec *s, ap_dbd_t *sql)
+DBD_DECLARE_NONSTD(void) ap_dbd_close(server_rec *s, ap_dbd_t *rec)
 {
     svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
-    if (!svr->persist) {
-        dbd_close((void*) sql);
+
+    if (!svr->cfg->persist) {
+        apr_pool_destroy(rec->pool);
     }
 #if APR_HAS_THREADS
     else {
-        apr_reslist_release(svr->dbpool, sql);
+        apr_reslist_release(svr->group->reslist, rec);
     }
 #endif
 }
-#define arec ((ap_dbd_t*)rec)
-#if APR_HAS_THREADS
+
+static apr_status_t dbd_check(apr_pool_t *pool, server_rec *s, ap_dbd_t *rec)
+{
+    svr_cfg *svr;
+    apr_status_t rv = apr_dbd_check_conn(rec->driver, pool, rec->handle);
+    const char *errmsg;
+
+    if ((rv == APR_SUCCESS) || (rv == APR_ENOTIMPL)) {
+        return APR_SUCCESS;
+    }
+
+    errmsg = apr_dbd_error(rec->driver, rec->handle, rv);
+    if (!errmsg) {
+        errmsg = "(unknown)";
+    }
+
+    svr = ap_get_module_config(s->module_config, &dbd_module);
+    ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
+                 "DBD [%s] Error: %s", svr->cfg->name, errmsg);
+    return rv;
+}
+
 DBD_DECLARE_NONSTD(ap_dbd_t*) ap_dbd_open(apr_pool_t *pool, server_rec *s)
 {
-    void *rec = NULL;
     svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
-    apr_status_t rv = APR_SUCCESS;
-    const char *errmsg;
+    dbd_group_t *group = svr->group;
+    dbd_cfg_t *cfg = svr->cfg;
+    ap_dbd_t *rec = NULL;
+#if APR_HAS_THREADS
+    apr_status_t rv;
+#endif
 
     /* If nothing is configured, we shouldn't be here */
-    if (svr->name == no_dbdriver) {
-        ap_log_perror(APLOG_MARK, APLOG_ERR, 0, pool, "DBD: not configured");
+    if (cfg->name == no_dbdriver) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "DBD: not configured");
         return NULL;
     }
 
-    if (!svr->persist) {
+    if (!cfg->persist) {
         /* Return a once-only connection */
-        rv = dbd_construct(&rec, svr, s->process->pool);
-        return (rv == APR_SUCCESS) ? arec : NULL;
+        group = apr_pcalloc(pool, sizeof(dbd_group_t));
+
+        group->cfg = cfg;
+
+        dbd_construct((void*) &rec, group, pool);
+        return rec;
     }
 
-    if (!svr->dbpool) {
-        if (dbd_setup_lock(pool, s) != APR_SUCCESS) {
+#if APR_HAS_THREADS
+    if (!group->reslist) {
+        if (dbd_setup_lock(s, group) != APR_SUCCESS) {
             return NULL;
         }
     }
-    rv = apr_reslist_acquire(svr->dbpool, &rec);
+
+    rv = apr_reslist_acquire(group->reslist, (void*) &rec);
     if (rv != APR_SUCCESS) {
-        ap_log_perror(APLOG_MARK, APLOG_ERR, rv, pool,
-                      "Failed to acquire DBD connection from pool!");
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
+                     "Failed to acquire DBD connection from pool!");
         return NULL;
     }
-    rv = apr_dbd_check_conn(arec->driver, pool, arec->handle);
-    if ((rv != APR_SUCCESS) && (rv != APR_ENOTIMPL)) {
-        errmsg = apr_dbd_error(arec->driver, arec->handle, rv);
-        if (!errmsg) {
-            errmsg = "(unknown)";
-        }
-        ap_log_perror(APLOG_MARK, APLOG_ERR, rv, pool,
-                      "DBD[%s] Error: %s", svr->name, errmsg );
-        apr_reslist_invalidate(svr->dbpool, rec);
+
+    if (dbd_check(pool, s, rec) != APR_SUCCESS) {
+        apr_reslist_invalidate(group->reslist, rec);
         return NULL;
     }
-    return arec;
-}
 #else
-DBD_DECLARE_NONSTD(ap_dbd_t*) ap_dbd_open(apr_pool_t *pool, server_rec *s)
-{
-    apr_status_t rv = APR_SUCCESS;
-    const char *errmsg;
-    void *rec = NULL;
-    svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
-
-    /* If nothing is configured, we shouldn't be here */
-    if (svr->name == no_dbdriver) {
-        ap_log_perror(APLOG_MARK, APLOG_ERR, 0, pool, "DBD: not configured");
-        return NULL;
+    /* If we have a persistent connection and it's good, we'll use it;
+     * since this is non-threaded, we can update without a mutex
+     */
+    rec = group->rec;
+    if (rec) {
+        if (dbd_check(pool, s, rec) != APR_SUCCESS) {
+            apr_pool_destroy(rec->pool);
+            rec = NULL;
+        }
     }
 
-    if (!svr->persist) {
-        /* Return a once-only connection */
-        rv = dbd_construct(&rec, svr, s->process->pool);
-        return (rv == APR_SUCCESS) ? arec : NULL;
+    /* We don't have a connection right now, so we'll open one */
+    if (!rec) {
+        dbd_construct((void*) &rec, group, group->pool);
+        group->rec = rec;
     }
+#endif
 
-/* since we're in nothread-land, we can mess with svr->conn with impunity */
-/* If we have a persistent connection and it's good, we'll use it */
-    if (svr->conn) {
-        rv = apr_dbd_check_conn(svr->conn->driver, pool, svr->conn->handle);
-        if ((rv != APR_SUCCESS) && (rv != APR_ENOTIMPL)) {
-            errmsg = apr_dbd_error(arec->driver, arec->handle, rv);
-            if (!errmsg) {
-                errmsg = "(unknown)";
-            }
-            ap_log_perror(APLOG_MARK, APLOG_ERR, rv, pool,
-                          "DBD[%s] Error: %s", svr->name, errmsg);
-            svr->conn = NULL;
-        }
-    }
-/* We don't have a connection right now, so we'll open one */
-    if (!svr->conn) {
-        if (dbd_construct(&rec, svr, s->process->pool) == APR_SUCCESS) {
-            svr->conn = arec ;
-            apr_pool_cleanup_register(s->process->pool, svr->conn,
-                                      dbd_close, apr_pool_cleanup_null);
-        }
-    }
-    return svr->conn;
+    return rec;
 }
-#endif
+
 #if APR_HAS_THREADS
 typedef struct {
-    ap_dbd_t *conn;
-    apr_reslist_t *dbpool;
-} dbd_pool_rec;
-static apr_status_t dbd_release(void *REQ)
+    ap_dbd_t *rec;
+    apr_reslist_t *reslist;
+} dbd_acquire_t;
+
+static apr_status_t dbd_release(void *data)
 {
-    dbd_pool_rec *req = REQ;
-    apr_reslist_release(req->dbpool, req->conn);
+    dbd_acquire_t *acq = data;
+    apr_reslist_release(acq->reslist, acq->rec);
     return APR_SUCCESS;
 }
+
 DBD_DECLARE_NONSTD(ap_dbd_t *) ap_dbd_acquire(request_rec *r)
 {
-    svr_cfg *svr;
-    dbd_pool_rec *req;
+    dbd_acquire_t *acq;
 
     while (!ap_is_initial_req(r)) {
         if (r->prev) {
             r = r->prev;
         }
         else if (r->main) {
             r = r->main;
         }
     }
 
-    req = ap_get_module_config(r->request_config, &dbd_module);
-    if (!req) {
-        req = apr_palloc(r->pool, sizeof(dbd_pool_rec));
-        req->conn = ap_dbd_open(r->pool, r->server);
-        if (req->conn) {
-            svr = ap_get_module_config(r->server->module_config, &dbd_module);
-            ap_set_module_config(r->request_config, &dbd_module, req);
-            if (svr->persist) {
-                req->dbpool = svr->dbpool;
-                apr_pool_cleanup_register(r->pool, req, dbd_release,
-                                          apr_pool_cleanup_null);
-            }
-            else {
-                apr_pool_cleanup_register(r->pool, req->conn, dbd_close,
+    acq = ap_get_module_config(r->request_config, &dbd_module);
+    if (!acq) {
+        acq = apr_palloc(r->pool, sizeof(dbd_acquire_t));
+        acq->rec = ap_dbd_open(r->pool, r->server);
+        if (acq->rec) {
+            svr_cfg *svr = ap_get_module_config(r->server->module_config,
+                                                &dbd_module);
+
+            ap_set_module_config(r->request_config, &dbd_module, acq);
+            if (svr->cfg->persist) {
+                acq->reslist = svr->group->reslist;
+                apr_pool_cleanup_register(r->pool, acq, dbd_release,
                                           apr_pool_cleanup_null);
             }
         }
     }
-    return req->conn;
+
+    return acq->rec;
 }
+
 DBD_DECLARE_NONSTD(ap_dbd_t *) ap_dbd_cacquire(conn_rec *c)
 {
-    svr_cfg *svr;
-    dbd_pool_rec *req = ap_get_module_config(c->conn_config, &dbd_module);
-    if (!req) {
-        req = apr_palloc(c->pool, sizeof(dbd_pool_rec));
-        req->conn = ap_dbd_open(c->pool, c->base_server);
-        if (req->conn) {
-            svr = ap_get_module_config(c->base_server->module_config, &dbd_module);
-            ap_set_module_config(c->conn_config, &dbd_module, req);
-            if (svr->persist) {
-                req->dbpool = svr->dbpool;
-                apr_pool_cleanup_register(c->pool, req, dbd_release,
-                                          apr_pool_cleanup_null);
-            }
-            else {
-                apr_pool_cleanup_register(c->pool, req->conn, dbd_close,
+    dbd_acquire_t *acq = ap_get_module_config(c->conn_config, &dbd_module);
+
+    if (!acq) {
+        acq = apr_palloc(c->pool, sizeof(dbd_acquire_t));
+        acq->rec = ap_dbd_open(c->pool, c->base_server);
+        if (acq->rec) {
+            svr_cfg *svr = ap_get_module_config(c->base_server->module_config,
+                                                &dbd_module);
+
+            ap_set_module_config(c->conn_config, &dbd_module, acq);
+            if (svr->cfg->persist) {
+                acq->reslist = svr->group->reslist;
+                apr_pool_cleanup_register(c->pool, acq, dbd_release,
                                           apr_pool_cleanup_null);
             }
         }
     }
-    return req->conn;
+
+    return acq->rec;
 }
 #else
 DBD_DECLARE_NONSTD(ap_dbd_t *) ap_dbd_acquire(request_rec *r)
 {
-    svr_cfg *svr;
-    ap_dbd_t *ret;
+    ap_dbd_t *rec;
 
     while (!ap_is_initial_req(r)) {
         if (r->prev) {
             r = r->prev;
         }
         else if (r->main) {
             r = r->main;
         }
     }
 
-    ret = ap_get_module_config(r->request_config, &dbd_module);
-    if (!ret) {
-        svr = ap_get_module_config(r->server->module_config, &dbd_module);
-        ret = ap_dbd_open(r->pool, r->server);
-        if (ret) {
-            ap_set_module_config(r->request_config, &dbd_module, ret);
-            if (!svr->persist) {
-                apr_pool_cleanup_register(r->pool, svr->conn, dbd_close,
-                                          apr_pool_cleanup_null);
-            }
-            /* if persist then dbd_open registered cleanup on proc pool */
+    rec = ap_get_module_config(r->request_config, &dbd_module);
+    if (!rec) {
+        rec = ap_dbd_open(r->pool, r->server);
+        if (rec) {
+            ap_set_module_config(r->request_config, &dbd_module, rec);
         }
     }
-    return ret;
+
+    return rec;
 }
+
 DBD_DECLARE_NONSTD(ap_dbd_t *) ap_dbd_cacquire(conn_rec *c)
 {
-    svr_cfg *svr;
-    ap_dbd_t *ret = ap_get_module_config(c->conn_config, &dbd_module);
-    if (!ret) {
-        svr = ap_get_module_config(c->base_server->module_config, &dbd_module);
-        ret = ap_dbd_open(c->pool, c->base_server);
-        if (ret) {
-            ap_set_module_config(c->conn_config, &dbd_module, ret);
-            if (!svr->persist) {
-                apr_pool_cleanup_register(c->pool, svr->conn, dbd_close,
-                                          apr_pool_cleanup_null);
-            }
-            /* if persist then dbd_open registered cleanup on proc pool */
+    ap_dbd_t *rec = ap_get_module_config(c->conn_config, &dbd_module);
+
+    if (!rec) {
+        rec = ap_dbd_open(c->pool, c->base_server);
+        if (rec) {
+            ap_set_module_config(c->conn_config, &dbd_module, rec);
         }
     }
-    return ret;
+
+    return rec;
 }
 #endif
 
-static int dbd_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
-{
-   dbd_prepared_defns = apr_hash_make(ptemp);
-   return OK;
-}
-static int dbd_post_config(apr_pool_t *pconf, apr_pool_t *plog,
-                           apr_pool_t *ptemp, server_rec *s)
-{
-    svr_cfg *svr;
-    server_rec *sp;
-    for (sp = s; sp; sp = sp->next) {
-        const char *key = apr_psprintf(s->process->pool, "%pp", s);
-        svr = ap_get_module_config(sp->module_config, &dbd_module);
-        svr->prepared = apr_hash_get(dbd_prepared_defns, key,
-                                     APR_HASH_KEY_STRING);
-    }
-    return OK;
-}
 static void dbd_hooks(apr_pool_t *pool)
 {
-#if APR_HAS_THREADS
+    ap_hook_pre_config(dbd_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_post_config(dbd_post_config, NULL, NULL, APR_HOOK_MIDDLE);
     ap_hook_child_init((void*)dbd_setup_init, NULL, NULL, APR_HOOK_MIDDLE);
-#endif
+
+    APR_REGISTER_OPTIONAL_FN(ap_dbd_prepare);
     APR_REGISTER_OPTIONAL_FN(ap_dbd_open);
     APR_REGISTER_OPTIONAL_FN(ap_dbd_close);
     APR_REGISTER_OPTIONAL_FN(ap_dbd_acquire);
     APR_REGISTER_OPTIONAL_FN(ap_dbd_cacquire);
-    APR_REGISTER_OPTIONAL_FN(ap_dbd_prepare);
+
     apr_dbd_init(pool);
-    ap_hook_pre_config(dbd_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
-    ap_hook_post_config(dbd_post_config, NULL, NULL, APR_HOOK_MIDDLE);
 }
 
 module AP_MODULE_DECLARE_DATA dbd_module = {
     STANDARD20_MODULE_STUFF,
     NULL,
     NULL,
-    dbd_cfg,
-    dbd_merge,
+    create_dbd_config,
+    merge_dbd_config,
     dbd_cmds,
     dbd_hooks
 };
+
