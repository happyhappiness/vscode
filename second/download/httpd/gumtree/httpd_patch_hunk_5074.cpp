      *     the TZ value specially.  We could use that, but it would mean
      *     parsing the key/value pairs back OUT of the allocated env array,
      *     not to mention allocating a totally useless array in the first
      *     place, which would suck. */
 
     envarr = apr_table_elts(r->subprocess_env);
-
     elts = (const apr_table_entry_t *) envarr->elts;
 
-    for (i = 0; i < envarr->nelts; ++i) {
-        apr_size_t keylen, vallen;
-
-        if (! elts[i].key) {
-            continue;
-        }
-
-        keylen = strlen(elts[i].key);
-
-        if (keylen >> 7 == 0) {
-            envlen += 1;
-        }
-        else {
-            envlen += 4;
-        }
-
-        envlen += keylen;
-
-        vallen = strlen(elts[i].val);
-
 #ifdef FCGI_DUMP_ENV_VARS
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01062)
-                      "sending env var '%s' value '%s'",
-                      elts[i].key, elts[i].val);
-#endif
-
-        if (vallen >> 7 == 0) {
-            envlen += 1;
+    {
+        int i;
+        
+        for (i = 0; i < envarr->nelts; ++i) {
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01062)
+                          "sending env var '%s' value '%s'",
+                          elts[i].key, elts[i].val);
         }
-        else {
-            envlen += 4;
-        }
-
-        envlen += vallen;
-
-        /* The cast of bodylen is safe since FCGI_MAX_ENV_SIZE is for sure an int */
-        if (envlen > FCGI_MAX_ENV_SIZE) {
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01063)
-                          "truncating environment to %d bytes and %d elements",
-                          (int)bodylen, i);
-            break;
-        }
-
-        bodylen = envlen;
     }
+#endif
 
-    numenv = i;
-
-    body = apr_pcalloc(r->pool, bodylen);
-
-    itr = body;
-
-    for (i = 0; i < numenv; ++i) {
-        apr_size_t keylen, vallen;
-
-        if (! elts[i].key) {
-            continue;
-        }
-
-        keylen = strlen(elts[i].key);
+    /* Send envvars over in as many FastCGI records as it takes, */
+    next_elem = 0; /* starting with the first one */
 
-        if (keylen >> 7 == 0) {
-            itr[0] = keylen & 0xff;
-            itr += 1;
-        }
-        else {
-            itr[0] = ((keylen >> 24) & 0xff) | 0x80;
-            itr[1] = ((keylen >> 16) & 0xff);
-            itr[2] = ((keylen >> 8) & 0xff);
-            itr[3] = ((keylen) & 0xff);
-            itr += 4;
+    avail_len = 16 * 1024; /* our limit per record, which could have been up
+                            * to AP_FCGI_MAX_CONTENT_LEN
+                            */
+
+    while (next_elem < envarr->nelts) {
+        starting_elem = next_elem;
+        required_len = ap_fcgi_encoded_env_len(r->subprocess_env,
+                                               avail_len,
+                                               &next_elem);
+
+        if (!required_len) {
+            if (next_elem < envarr->nelts) {
+                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+                              APLOGNO(02536) "couldn't encode envvar '%s' in %"
+                              APR_SIZE_T_FMT " bytes",
+                              elts[next_elem].key, avail_len);
+                /* skip this envvar and continue */
+                ++next_elem;
+                continue;
+            }
+            /* only an unused element at the end of the array */
+            break;
         }
 
-        vallen = strlen(elts[i].val);
-
-        if (vallen >> 7 == 0) {
-            itr[0] = vallen & 0xff;
-            itr += 1;
-        }
-        else {
-            itr[0] = ((vallen >> 24) & 0xff) | 0x80;
-            itr[1] = ((vallen >> 16) & 0xff);
-            itr[2] = ((vallen >> 8) & 0xff);
-            itr[3] = ((vallen) & 0xff);
-            itr += 4;
+        body = apr_palloc(temp_pool, required_len);
+        rv = ap_fcgi_encode_env(r, r->subprocess_env, body, required_len,
+                                &starting_elem);
+        /* we pre-compute, so we can't run out of space */
+        ap_assert(rv == APR_SUCCESS);
+        /* compute and encode must be in sync */
+        ap_assert(starting_elem == next_elem);
+
+        ap_fcgi_fill_in_header(&header, AP_FCGI_PARAMS, request_id,
+                               (apr_uint16_t)required_len, 0);
+        ap_fcgi_header_to_array(&header, farray);
+
+        vec[0].iov_base = (void *)farray;
+        vec[0].iov_len = sizeof(farray);
+        vec[1].iov_base = body;
+        vec[1].iov_len = required_len;
+
+        rv = send_data(conn, vec, 2, &len, 1);
+        apr_pool_clear(temp_pool);
+
+        if (rv) {
+            return rv;
         }
-
-        memcpy(itr, elts[i].key, keylen);
-        itr += keylen;
-
-        memcpy(itr, elts[i].val, vallen);
-        itr += vallen;
-    }
-
-    fill_in_header(&header, FCGI_PARAMS, request_id, bodylen, 0);
-    fcgi_header_to_array(&header, farray);
-
-    vec[0].iov_base = (void *)farray;
-    vec[0].iov_len = sizeof(farray);
-    vec[1].iov_base = body;
-    vec[1].iov_len = bodylen;
-
-    rv = send_data(conn, vec, 2, &len, 1);
-    if (rv) {
-        return rv;
     }
 
-    fill_in_header(&header, FCGI_PARAMS, request_id, 0, 0);
-    fcgi_header_to_array(&header, farray);
+    /* Envvars sent, so say we're done */
+    ap_fcgi_fill_in_header(&header, AP_FCGI_PARAMS, request_id, 0, 0);
+    ap_fcgi_header_to_array(&header, farray);
 
     vec[0].iov_base = (void *)farray;
     vec[0].iov_len = sizeof(farray);
 
     return send_data(conn, vec, 1, &len, 1);
 }
