     if (conf->limit_xml_body < 0)
         return "LimitXMLRequestBody requires a non-negative integer.";
 
     return NULL;
 }
 
-AP_DECLARE(size_t) ap_get_limit_xml_body(const request_rec *r)
+static const char *set_max_ranges(cmd_parms *cmd, void *conf_, const char *arg)
+{
+    core_dir_config *conf = conf_;
+    int val = 0;
+
+    if (!strcasecmp(arg, "none")) {
+        val = AP_MAXRANGES_NORANGES;
+    }
+    else if (!strcasecmp(arg, "default")) {
+        val = AP_MAXRANGES_DEFAULT;
+    }
+    else if (!strcasecmp(arg, "unlimited")) {
+        val = AP_MAXRANGES_UNLIMITED;
+    }
+    else {
+        val = atoi(arg);
+        if (val <= 0)
+            return "MaxRanges requires 'none', 'default', 'unlimited' or "
+                   "a positive integer";
+    }
+
+    conf->max_ranges = val;
+
+    return NULL;
+}
+
+static const char *set_max_overlaps(cmd_parms *cmd, void *conf_, const char *arg)
+{
+    core_dir_config *conf = conf_;
+    int val = 0;
+
+    if (!strcasecmp(arg, "none")) {
+        val = AP_MAXRANGES_NORANGES;
+    }
+    else if (!strcasecmp(arg, "default")) {
+        val = AP_MAXRANGES_DEFAULT;
+    }
+    else if (!strcasecmp(arg, "unlimited")) {
+        val = AP_MAXRANGES_UNLIMITED;
+    }
+    else {
+        val = atoi(arg);
+        if (val <= 0)
+            return "MaxRangeOverlaps requires 'none', 'default', 'unlimited' or "
+            "a positive integer";
+    }
+
+    conf->max_overlaps = val;
+
+    return NULL;
+}
+
+static const char *set_max_reversals(cmd_parms *cmd, void *conf_, const char *arg)
+{
+    core_dir_config *conf = conf_;
+    int val = 0;
+
+    if (!strcasecmp(arg, "none")) {
+        val = AP_MAXRANGES_NORANGES;
+    }
+    else if (!strcasecmp(arg, "default")) {
+        val = AP_MAXRANGES_DEFAULT;
+    }
+    else if (!strcasecmp(arg, "unlimited")) {
+        val = AP_MAXRANGES_UNLIMITED;
+    }
+    else {
+        val = atoi(arg);
+        if (val <= 0)
+            return "MaxRangeReversals requires 'none', 'default', 'unlimited' or "
+            "a positive integer";
+    }
+
+    conf->max_reversals = val;
+
+    return NULL;
+}
+
+AP_DECLARE(apr_size_t) ap_get_limit_xml_body(const request_rec *r)
 {
     core_dir_config *conf;
 
-    conf = ap_get_module_config(r->per_dir_config, &core_module);
+    conf = ap_get_core_module_config(r->per_dir_config);
     if (conf->limit_xml_body == AP_LIMIT_UNSET)
         return AP_DEFAULT_LIMIT_XML_BODY;
 
-    return (size_t)conf->limit_xml_body;
+    return (apr_size_t)conf->limit_xml_body;
 }
 
 #if !defined (RLIMIT_CPU) || !(defined (RLIMIT_DATA) || defined (RLIMIT_VMEM) || defined(RLIMIT_AS)) || !defined (RLIMIT_NPROC)
 static const char *no_set_limit(cmd_parms *cmd, void *conf_,
                                 const char *arg, const char *arg2)
 {
-    ap_log_error(APLOG_MARK, APLOG_ERR, 0, cmd->server,
+    ap_log_error(APLOG_MARK, APLOG_ERR, 0, cmd->server, APLOGNO(00118)
                 "%s not supported on this platform", cmd->cmd->name);
 
     return NULL;
 }
 #endif
 
