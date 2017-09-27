                                 "113 Heuristic expiration");
             }
         }
         return 1;    /* Cache object is fresh (enough) */
     }
 
-    return 0;        /* Cache object is stale */
+    /*
+     * At this point we are stale, but: if we are under load, we may let
+     * a significant number of stale requests through before the first
+     * stale request successfully revalidates itself, causing a sudden
+     * unexpected thundering herd which in turn brings angst and drama.
+     *
+     * So.
+     *
+     * We want the first stale request to go through as normal. But the
+     * second and subsequent request, we must pretend to be fresh until
+     * the first request comes back with either new content or confirmation
+     * that the stale content is still fresh.
+     *
+     * To achieve this, we create a very simple file based lock based on
+     * the key of the cached object. We attempt to open the lock file with
+     * exclusive write access. If we succeed, woohoo! we're first, and we
+     * follow the stale path to the backend server. If we fail, oh well,
+     * we follow the fresh path, and avoid being a thundering herd.
+     *
+     * The lock lives only as long as the stale request that went on ahead.
+     * If the request succeeds, the lock is deleted. If the request fails,
+     * the lock is deleted, and another request gets to make a new lock
+     * and try again.
+     *
+     * At any time, a request marked "no-cache" will force a refresh,
+     * ignoring the lock, ensuring an extended lockout is impossible.
+     *
+     * A lock that exceeds a maximum age will be deleted, and another
+     * request gets to make a new lock and try again.
+     */
+    status = ap_cache_try_lock(conf, r, (char *)h->cache_obj->key);
+    if (APR_SUCCESS == status) {
+        /* we obtained a lock, follow the stale path */
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+                     "Cache lock obtained for stale cached URL, "
+                     "revalidating entry: %s",
+                     r->unparsed_uri);
+        return 0;
+    }
+    else if (APR_EEXIST == status) {
+        /* lock already exists, return stale data anyway, with a warning */
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+                     "Cache already locked for stale cached URL, "
+                     "pretend it is fresh: %s",
+                     r->unparsed_uri);
+
+        /* make sure we don't stomp on a previous warning */
+        warn_head = apr_table_get(h->resp_hdrs, "Warning");
+        if ((warn_head == NULL) ||
+            ((warn_head != NULL) && (ap_strstr_c(warn_head, "110") == NULL))) {
+            apr_table_merge(h->resp_hdrs, "Warning",
+                        "110 Response is stale");
+        }
+
+        return 1;
+    }
+    else {
+        /* some other error occurred, just treat the object as stale */
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, status, r->server,
+                     "Attempt to obtain a cache lock for stale "
+                     "cached URL failed, revalidating entry anyway: %s",
+                     r->unparsed_uri);
+        return 0;
+    }
+
 }
 
 /*
  * list is a comma-separated list of case-insensitive tokens, with
  * optional whitespace around the tokens.
  * The return returns 1 if the token val is found in the list, or 0
