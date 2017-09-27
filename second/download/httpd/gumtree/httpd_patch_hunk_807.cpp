         }
     }
 
     return NULL;
 }
 
+static const char *set_allow_opts(cmd_parms *cmd, allow_options_t *opts,
+                                  const char *l)
+{
+    allow_options_t opt;
+    int first = 1;
+
+    char *w, *p = (char *) l;
+    char *tok_state;
+
+    while ((w = apr_strtok(p, ",", &tok_state)) != NULL) {
+
+        if (first) {
+            p = NULL;
+            *opts = OPT_NONE;
+            first = 0;
+        }
+
+        if (!strcasecmp(w, "Indexes")) {
+            opt = OPT_INDEXES;
+        }
+        else if (!strcasecmp(w, "Includes")) {
+            opt = OPT_INCLUDES;
+        }
+        else if (!strcasecmp(w, "IncludesNOEXEC")) {
+            opt = (OPT_INCLUDES | OPT_INCNOEXEC);
+        }
+        else if (!strcasecmp(w, "FollowSymLinks")) {
+            opt = OPT_SYM_LINKS;
+        }
+        else if (!strcasecmp(w, "SymLinksIfOwnerMatch")) {
+            opt = OPT_SYM_OWNER;
+        }
+        else if (!strcasecmp(w, "ExecCGI")) {
+            opt = OPT_EXECCGI;
+        }
+        else if (!strcasecmp(w, "MultiViews")) {
+            opt = OPT_MULTI;
+        }
+        else if (!strcasecmp(w, "RunScripts")) { /* AI backcompat. Yuck */
+            opt = OPT_MULTI|OPT_EXECCGI;
+        }
+        else if (!strcasecmp(w, "None")) {
+            opt = OPT_NONE;
+        }
+        else if (!strcasecmp(w, "All")) {
+            opt = OPT_ALL;
+        }
+        else {
+            return apr_pstrcat(cmd->pool, "Illegal option ", w, NULL);
+        }
+
+        *opts |= opt;
+    }
+
+    (*opts) &= (~OPT_UNSET);
+
+    return NULL;
+}
+
 static const char *set_override(cmd_parms *cmd, void *d_, const char *l)
 {
     core_dir_config *d = d_;
     char *w;
+    char *k, *v;
 
     const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);
     if (err != NULL) {
         return err;
     }
 
+    /* Throw a warning if we're in <Location> or <Files> */
+    if (ap_check_cmd_context(cmd, NOT_IN_LOCATION | NOT_IN_FILES)) {
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
+                     "Useless use of AllowOverride in line %d.",
+                     cmd->directive->line_num);
+    }
+
     d->override = OR_NONE;
     while (l[0]) {
         w = ap_getword_conf(cmd->pool, &l);
+
+        k = w;
+        v = strchr(k, '=');
+        if (v) {
+                *v++ = '\0';
+        }
+
         if (!strcasecmp(w, "Limit")) {
             d->override |= OR_LIMIT;
         }
-        else if (!strcasecmp(w, "Options")) {
+        else if (!strcasecmp(k, "Options")) {
             d->override |= OR_OPTIONS;
+            if (v)
+                set_allow_opts(cmd, &(d->override_opts), v);
+            else
+                d->override_opts = OPT_ALL;
         }
         else if (!strcasecmp(w, "FileInfo")) {
             d->override |= OR_FILEINFO;
         }
         else if (!strcasecmp(w, "AuthConfig")) {
             d->override |= OR_AUTHCFG;
