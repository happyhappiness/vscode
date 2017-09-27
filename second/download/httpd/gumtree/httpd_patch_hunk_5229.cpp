     if (rv != APR_SUCCESS) {
         fprintf(stderr, "ab: Could not stat POST data file (%s): %s\n", pfile,
                 apr_strerror(rv, errmsg, sizeof errmsg));
         return rv;
     }
     postlen = (apr_size_t)finfo.size;
-    postdata = malloc(postlen);
-    if (!postdata) {
-        fprintf(stderr, "ab: Could not allocate POST data buffer\n");
-        return APR_ENOMEM;
-    }
+    postdata = xmalloc(postlen);
     rv = apr_file_read_full(postfd, postdata, postlen, NULL);
     if (rv != APR_SUCCESS) {
         fprintf(stderr, "ab: Could not read POST data file: %s\n",
                 apr_strerror(rv, errmsg, sizeof errmsg));
         return rv;
     }
