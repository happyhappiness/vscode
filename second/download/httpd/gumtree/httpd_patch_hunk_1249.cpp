     resident_time = now - info->response_time;
     current_age = corrected_initial_age + resident_time;
 
     return apr_time_sec(current_age);
 }
 
+/**
+ * Try obtain a cache wide lock on the given cache key.
+ *
+ * If we return APR_SUCCESS, we obtained the lock, and we are clear to
+ * proceed to the backend. If we return APR_EEXISTS, then the lock is
+ * already locked, someone else has gone to refresh the backend data
+ * already, so we must return stale data with a warning in the mean
+ * time. If we return anything else, then something has gone pear
+ * shaped, and we allow the request through to the backend regardless.
+ *
+ * This lock is created from the request pool, meaning that should
+ * something go wrong and the lock isn't deleted on return of the
+ * request headers from the backend for whatever reason, at worst the
+ * lock will be cleaned up when the request dies or finishes.
+ *
+ * If something goes truly bananas and the lock isn't deleted when the
+ * request dies, the lock will be trashed when its max-age is reached,
+ * or when a request arrives containing a Cache-Control: no-cache. At
+ * no point is it possible for this lock to permanently deny access to
+ * the backend.
+ */
+CACHE_DECLARE(apr_status_t) ap_cache_try_lock(cache_server_conf *conf,
+        request_rec *r, char *key) {
+    apr_status_t status;
+    const char *lockname;
+    const char *path;
+    char dir[5];
+    apr_time_t now = apr_time_now();
+    apr_finfo_t finfo;
+    apr_file_t *lockfile;
+    void *dummy;
+
+    finfo.mtime = 0;
+
+    if (!conf || !conf->lock || !conf->lockpath) {
+        /* no locks configured, leave */
+        return APR_SUCCESS;
+    }
+
+    /* lock already obtained earlier? if so, success */
+    apr_pool_userdata_get(&dummy, CACHE_LOCKFILE_KEY, r->pool);
+    if (dummy) {
+        return APR_SUCCESS;
+    }
+
+    /* create the key if it doesn't exist */
+    if (!key) {
+        cache_generate_key(r, r->pool, &key);
+    }
+
+    /* create a hashed filename from the key, and save it for later */
+    lockname = ap_cache_generate_name(r->pool, 0, 0, key);
+
+    /* lock files represent discrete just-went-stale URLs "in flight", so
+     * we support a simple two level directory structure, more is overkill.
+     */
+    dir[0] = '/';
+    dir[1] = lockname[0];
+    dir[2] = '/';
+    dir[3] = lockname[1];
+    dir[4] = 0;
+
+    /* make the directories */
+    path = apr_pstrcat(r->pool, conf->lockpath, dir, NULL);
+    if (APR_SUCCESS != (status = apr_dir_make_recursive(path,
+            APR_UREAD|APR_UWRITE|APR_UEXECUTE, r->pool))) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
+                     "Could not create a cache lock directory: %s",
+                     path);
+        return status;
+    }
+    lockname = apr_pstrcat(r->pool, path, "/", lockname, NULL);
+    apr_pool_userdata_set(lockname, CACHE_LOCKNAME_KEY, NULL, r->pool);
+
+    /* is an existing lock file too old? */
+    status = apr_stat(&finfo, lockname,
+                APR_FINFO_MTIME | APR_FINFO_NLINK, r->pool);
+    if (!(APR_STATUS_IS_ENOENT(status)) && APR_SUCCESS != status) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, APR_EEXIST, r->server,
+                     "Could not stat a cache lock file: %s",
+                     lockname);
+        return status;
+    }
+    if ((status == APR_SUCCESS) && (((now - finfo.mtime) > conf->lockmaxage)
+                                  || (now < finfo.mtime))) {
+        ap_log_error(APLOG_MARK, APLOG_INFO, status, r->server,
+                     "Cache lock file for '%s' too old, removing: %s",
+                     r->uri, lockname);
+        apr_file_remove(lockname, r->pool);
+    }
+
+    /* try obtain a lock on the file */
+    if (APR_SUCCESS == (status = apr_file_open(&lockfile, lockname,
+            APR_WRITE | APR_CREATE | APR_EXCL | APR_DELONCLOSE,
+            APR_UREAD | APR_UWRITE, r->pool))) {
+        apr_pool_userdata_set(lockfile, CACHE_LOCKFILE_KEY, NULL, r->pool);
+    }
+    return status;
+
+}
+
+/**
+ * Remove the cache lock, if present.
+ *
+ * First, try to close the file handle, whose delete-on-close should
+ * kill the file. Otherwise, just delete the file by name.
+ *
+ * If no lock name has yet been calculated, do the calculation of the
+ * lock name first before trying to delete the file.
+ *
+ * If an optional bucket brigade is passed, the lock will only be
+ * removed if the bucket brigade contains an EOS bucket.
+ */
+CACHE_DECLARE(apr_status_t) ap_cache_remove_lock(cache_server_conf *conf,
+        request_rec *r, char *key, apr_bucket_brigade *bb) {
+    void *dummy;
+    const char *lockname;
+
+    if (!conf || !conf->lock || !conf->lockpath) {
+        /* no locks configured, leave */
+        return APR_SUCCESS;
+    }
+    if (bb) {
+        apr_bucket *e;
+        int eos_found = 0;
+        for (e = APR_BRIGADE_FIRST(bb);
+             e != APR_BRIGADE_SENTINEL(bb);
+             e = APR_BUCKET_NEXT(e))
+        {
+            if (APR_BUCKET_IS_EOS(e)) {
+                eos_found = 1;
+                break;
+            }
+        }
+        if (!eos_found) {
+            /* no eos found in brigade, don't delete anything just yet,
+             * we are not done.
+             */
+            return APR_SUCCESS;
+        }
+    }
+    apr_pool_userdata_get(&dummy, CACHE_LOCKFILE_KEY, r->pool);
+    if (dummy) {
+        return apr_file_close((apr_file_t *)dummy);
+    }
+    apr_pool_userdata_get(&dummy, CACHE_LOCKNAME_KEY, r->pool);
+    lockname = (const char *)dummy;
+    if (!lockname) {
+        char dir[5];
+
+        /* create the key if it doesn't exist */
+        if (!key) {
+            cache_generate_key(r, r->pool, &key);
+        }
+
+        /* create a hashed filename from the key, and save it for later */
+        lockname = ap_cache_generate_name(r->pool, 0, 0, key);
+
+        /* lock files represent discrete just-went-stale URLs "in flight", so
+         * we support a simple two level directory structure, more is overkill.
+         */
+        dir[0] = '/';
+        dir[1] = lockname[0];
+        dir[2] = '/';
+        dir[3] = lockname[1];
+        dir[4] = 0;
+
+        lockname = apr_pstrcat(r->pool, conf->lockpath, dir, "/", lockname, NULL);
+    }
+    return apr_file_remove(lockname, r->pool);
+}
+
 CACHE_DECLARE(int) ap_cache_check_freshness(cache_handle_t *h,
                                             request_rec *r)
 {
+    apr_status_t status;
     apr_int64_t age, maxage_req, maxage_cresp, maxage, smaxage, maxstale;
     apr_int64_t minfresh;
     const char *cc_cresp, *cc_req;
     const char *pragma;
     const char *agestr = NULL;
     const char *expstr = NULL;
     char *val;
     apr_time_t age_c = 0;
     cache_info *info = &(h->cache_obj->info);
+    const char *warn_head;
     cache_server_conf *conf =
       (cache_server_conf *)ap_get_module_config(r->server->module_config,
                                                 &cache_module);
 
     /*
      * We now want to check if our cached data is still fresh. This depends
