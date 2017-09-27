     return strcmp(f1->fname,f2->fname);
 }
 
 static void process_resource_config_nofnmatch(server_rec *s, const char *fname,
                                               ap_directive_t **conftree,
                                               apr_pool_t *p,
-                                              apr_pool_t *ptemp)
+                                              apr_pool_t *ptemp,
+                                              unsigned depth)
 {
     cmd_parms parms;
     ap_configfile_t *cfp;
     const char *errmsg;
 
-    if (ap_is_rdirectory(p, fname)) {
+    if (ap_is_directory(p, fname)) {
         apr_dir_t *dirp;
         apr_finfo_t dirent;
         int current;
         apr_array_header_t *candidates = NULL;
         fnames *fnew;
         apr_status_t rv;
         char errmsg[120], *path = apr_pstrdup(p, fname);
 
+        if (++depth > AP_MAX_INCLUDE_DIR_DEPTH) {
+            fprintf(stderr, "%s: Directory %s exceeds the maximum include "
+                    "directory nesting level of %u. You have probably a "
+                    "recursion somewhere.\n", ap_server_argv0, path,
+                    AP_MAX_INCLUDE_DIR_DEPTH);
+            exit(1);
+        }
+
         /*
          * first course of business is to grok all the directory
          * entries here and store 'em away. Recall we need full pathnames
          * for this.
          */
         rv = apr_dir_open(&dirp, path, p);
