              * This code makes the assumption that the storage manager will
              * cache the req_hdrs if the response contains a Vary
              * header.
              *
              * RFC2616 13.6 and 14.44 describe the Vary mechanism.
              */
-            vary = apr_pstrdup(r->pool, apr_table_get(h->resp_hdrs, "Vary"));
-            while (vary && *vary) {
-                char *name = vary;
+            vary = cache_strqtok(
+                    apr_pstrdup(r->pool,
+                            cache_table_getm(r->pool, h->resp_hdrs, "Vary")),
+                    CACHE_SEPARATOR, &last);
+            while (vary) {
                 const char *h1, *h2;
 
-                /* isolate header name */
-                while (*vary && !apr_isspace(*vary) && (*vary != ','))
-                    ++vary;
-                while (*vary && (apr_isspace(*vary) || (*vary == ','))) {
-                    *vary = '\0';
-                    ++vary;
-                }
-
                 /*
                  * is this header in the request and the header in the cached
                  * request identical? If not, we give up and do a straight get
                  */
-                h1 = apr_table_get(r->headers_in, name);
-                h2 = apr_table_get(h->req_hdrs, name);
+                h1 = cache_table_getm(r->pool, r->headers_in, vary);
+                h2 = cache_table_getm(r->pool, h->req_hdrs, vary);
                 if (h1 == h2) {
                     /* both headers NULL, so a match - do nothing */
                 }
                 else if (h1 && h2 && !strcmp(h1, h2)) {
                     /* both headers exist and are equal - do nothing */
                 }
                 else {
                     /* headers do not match, so Vary failed */
                     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
-                            r, APLOGNO(00694) "cache_select_url(): Vary header mismatch.");
+                            r, APLOGNO(00694) "cache_select(): Vary header mismatch.");
                     mismatch = 1;
+                    break;
                 }
+                vary = cache_strqtok(NULL, CACHE_SEPARATOR, &last);
             }
 
             /* no vary match, try next provider */
             if (mismatch) {
                 /* try again with next cache type */
                 list = list->next;
                 continue;
             }
 
             cache->provider = list->provider;
             cache->provider_name = list->provider_name;
 
+            /*
+             * RFC2616 13.3.4 Rules for When to Use Entity Tags and Last-Modified
+             * Dates: An HTTP/1.1 caching proxy, upon receiving a conditional request
+             * that includes both a Last-Modified date and one or more entity tags as
+             * cache validators, MUST NOT return a locally cached response to the
+             * client unless that cached response is consistent with all of the
+             * conditional header fields in the request.
+             */
+            if (ap_condition_if_match(r, h->resp_hdrs) == AP_CONDITION_NOMATCH
+                    || ap_condition_if_unmodified_since(r, h->resp_hdrs)
+                            == AP_CONDITION_NOMATCH
+                    || ap_condition_if_none_match(r, h->resp_hdrs)
+                            == AP_CONDITION_NOMATCH
+                    || ap_condition_if_modified_since(r, h->resp_hdrs)
+                            == AP_CONDITION_NOMATCH
+                    || ap_condition_if_range(r, h->resp_hdrs) == AP_CONDITION_NOMATCH) {
+                mismatch = 1;
+            }
+
             /* Is our cached response fresh enough? */
-            fresh = cache_check_freshness(h, cache, r);
-            if (!fresh) {
+            if (mismatch || !cache_check_freshness(h, cache, r)) {
                 const char *etag, *lastmod;
 
                 /* Cache-Control: only-if-cached and revalidation required, try
                  * the next provider
                  */
                 if (cache->control_in.only_if_cached) {
