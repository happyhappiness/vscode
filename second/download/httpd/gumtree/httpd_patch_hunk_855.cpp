             /*
              * Now recurse these... we handle errors and subdirectories
              * via the recursion, which is nice
              */
             for (current = 0; current < candidates->nelts; ++current) {
                 fnew = &((fnames *) candidates->elts)[current];
-                process_resource_config_nofnmatch(s, fnew->fname, conftree, p,
-                                                  ptemp, depth);
+                error = process_resource_config_nofnmatch(s, fnew->fname,
+                                                          conftree, p, ptemp,
+                                                          depth);
+                if (error) {
+                    return error;
+                }
             }
         }
 
-        return;
+        return NULL;
     }
 
     /* GCC's initialization extensions are soooo nice here... */
     parms = default_parms;
     parms.pool = p;
     parms.temp_pool = ptemp;
     parms.server = s;
     parms.override = (RSRC_CONF | OR_ALL) & ~(OR_AUTHCFG | OR_LIMIT);
+    parms.override_opts = OPT_ALL | OPT_INCNOEXEC | OPT_SYM_OWNER | OPT_MULTI;
 
-    if (ap_pcfg_openfile(&cfp, p, fname) != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                     "%s: could not open document config file %s",
-                     ap_server_argv0, fname);
-        exit(1);
+    rv = ap_pcfg_openfile(&cfp, p, fname);
+    if (rv != APR_SUCCESS) {
+        char errmsg[120];
+        return apr_psprintf(p, "Could not open configuration file %s: %s",
+                            fname, apr_strerror(rv, errmsg, sizeof errmsg));
     }
 
     parms.config_file = cfp;
+    error = ap_build_config(&parms, p, ptemp, conftree);
+    ap_cfg_closefile(cfp);
 
-    errmsg = ap_build_config(&parms, p, ptemp, conftree);
-
-    if (errmsg != NULL) {
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                     "Syntax error on line %d of %s:",
-                     parms.err_directive->line_num,
-                     parms.err_directive->filename);
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                     "%s", errmsg);
-        exit(1);
+    if (error) {
+        return apr_psprintf(p, "Syntax error on line %d of %s: %s",
+                            parms.err_directive->line_num,
+                            parms.err_directive->filename, error);
     }
 
-    ap_cfg_closefile(cfp);
-
-    return;
+    return NULL;
 }
 
-AP_DECLARE(void) ap_process_resource_config(server_rec *s, const char *fname,
-                                            ap_directive_t **conftree,
-                                            apr_pool_t *p,
-                                            apr_pool_t *ptemp)
+AP_DECLARE(const char *) ap_process_resource_config(server_rec *s,
+                                                    const char *fname,
+                                                    ap_directive_t **conftree,
+                                                    apr_pool_t *p,
+                                                    apr_pool_t *ptemp)
 {
     /* XXX: lstat() won't work on the wildcard pattern...
      */
 
     /* don't require conf/httpd.conf if we have a -C or -c switch */
     if ((ap_server_pre_read_config->nelts
         || ap_server_post_read_config->nelts)
         && !(strcmp(fname, ap_server_root_relative(p, SERVER_CONFIG_FILE)))) {
         apr_finfo_t finfo;
 
-        if (apr_lstat(&finfo, fname, APR_FINFO_TYPE, p) != APR_SUCCESS)
-            return;
+        if (apr_stat(&finfo, fname, APR_FINFO_LINK | APR_FINFO_TYPE, p) != APR_SUCCESS)
+            return NULL;
     }
 
     if (!apr_fnmatch_test(fname)) {
-        process_resource_config_nofnmatch(s, fname, conftree, p, ptemp, 0);
+        return process_resource_config_nofnmatch(s, fname, conftree, p, ptemp,
+                                                 0);
     }
     else {
         apr_dir_t *dirp;
         apr_finfo_t dirent;
         int current;
         apr_array_header_t *candidates = NULL;
         fnames *fnew;
         apr_status_t rv;
-        char errmsg[120], *path = apr_pstrdup(p, fname), *pattern = NULL;
+        char *path = apr_pstrdup(p, fname), *pattern = NULL;
 
         pattern = ap_strrchr(path, '/');
 
         AP_DEBUG_ASSERT(pattern != NULL); /* path must be absolute. */
 
         *pattern++ = '\0';
 
         if (apr_fnmatch_test(path)) {
-            fprintf(stderr, "%s: wildcard patterns not allowed in Include "
-                    "%s\n", ap_server_argv0, fname);
-            exit(1);
+            return apr_pstrcat(p, "Wildcard patterns not allowed in Include ",
+                               fname, NULL);
         }
 
-        if (!ap_is_directory(p, path)){ 
-            fprintf(stderr, "%s: Include directory '%s' not found",
-                    ap_server_argv0, path);
-            exit(1);
+        if (!ap_is_directory(p, path)){
+            return apr_pstrcat(p, "Include directory '", path, "' not found",
+                               NULL);
         }
 
         if (!apr_fnmatch_test(pattern)) {
-            fprintf(stderr, "%s: must include a wildcard pattern "
-                    "for Include %s\n", ap_server_argv0, fname);
-            exit(1);
+            return apr_pstrcat(p, "Must include a wildcard pattern for "
+                               "Include ", fname, NULL);
         }
 
         /*
          * first course of business is to grok all the directory
          * entries here and store 'em away. Recall we need full pathnames
          * for this.
          */
         rv = apr_dir_open(&dirp, path, p);
         if (rv != APR_SUCCESS) {
-            fprintf(stderr, "%s: could not open config directory %s: %s\n",
-                    ap_server_argv0, path,
-                    apr_strerror(rv, errmsg, sizeof errmsg));
-            exit(1);
+            char errmsg[120];
+            return apr_psprintf(p, "Could not open config directory %s: %s",
+                                path, apr_strerror(rv, errmsg, sizeof errmsg));
         }
 
         candidates = apr_array_make(p, 1, sizeof(fnames));
         while (apr_dir_read(&dirent, APR_FINFO_DIRENT, dirp) == APR_SUCCESS) {
             /* strip out '.' and '..' */
             if (strcmp(dirent.name, ".")
                 && strcmp(dirent.name, "..")
                 && (apr_fnmatch(pattern, dirent.name,
-                                FNM_PERIOD) == APR_SUCCESS)) {
+                                APR_FNM_PERIOD) == APR_SUCCESS)) {
                 fnew = (fnames *) apr_array_push(candidates);
                 fnew->fname = ap_make_full_path(p, path, dirent.name);
             }
         }
 
         apr_dir_close(dirp);
         if (candidates->nelts != 0) {
+            const char *error;
+
             qsort((void *) candidates->elts, candidates->nelts,
                   sizeof(fnames), fname_alphasort);
 
             /*
              * Now recurse these... we handle errors and subdirectories
              * via the recursion, which is nice
              */
             for (current = 0; current < candidates->nelts; ++current) {
                 fnew = &((fnames *) candidates->elts)[current];
-                process_resource_config_nofnmatch(s, fnew->fname, conftree, p,
-                                                  ptemp, 0);
+                error = process_resource_config_nofnmatch(s, fnew->fname,
+                                                          conftree, p,
+                                                          ptemp, 0);
+                if (error) {
+                    return error;
+                }
             }
         }
     }
 
-    return;
+    return NULL;
 }
 
-AP_DECLARE(void) ap_process_config_tree(server_rec *s,
-                                        ap_directive_t *conftree,
-                                        apr_pool_t *p, apr_pool_t *ptemp)
+AP_DECLARE(int) ap_process_config_tree(server_rec *s,
+                                       ap_directive_t *conftree,
+                                       apr_pool_t *p,
+                                       apr_pool_t *ptemp)
 {
     const char *errmsg;
     cmd_parms parms;
 
     parms = default_parms;
     parms.pool = p;
     parms.temp_pool = ptemp;
     parms.server = s;
     parms.override = (RSRC_CONF | OR_ALL) & ~(OR_AUTHCFG | OR_LIMIT);
+    parms.override_opts = OPT_ALL | OPT_INCNOEXEC | OPT_SYM_OWNER | OPT_MULTI;
     parms.limited = -1;
 
     errmsg = ap_walk_config(conftree, &parms, s->lookup_defaults);
     if (errmsg) {
         ap_log_perror(APLOG_MARK, APLOG_STARTUP, 0, p,
                      "Syntax error on line %d of %s:",
                      parms.err_directive->line_num,
                      parms.err_directive->filename);
         ap_log_perror(APLOG_MARK, APLOG_STARTUP, 0, p,
                      "%s", errmsg);
-        exit(1);
+        return HTTP_INTERNAL_SERVER_ERROR;
     }
+
+    return OK;
 }
 
 AP_CORE_DECLARE(int) ap_parse_htaccess(ap_conf_vector_t **result,
                                        request_rec *r, int override,
+                                       int override_opts,
                                        const char *d, const char *access_name)
 {
     ap_configfile_t *f = NULL;
     cmd_parms parms;
     char *filename = NULL;
     const struct htaccess_result *cache;
