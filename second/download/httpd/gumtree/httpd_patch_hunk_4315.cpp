     while (apr_isspace(*strend))
         ++strend;
     *line = strend;
     return res;
 }
 
+AP_DECLARE(char *) ap_getword_conf2_nc(apr_pool_t *p, char **line)
+{
+    return ap_getword_conf2(p, (const char **) line);
+}
+
+AP_DECLARE(char *) ap_getword_conf2(apr_pool_t *p, const char **line)
+{
+    const char *str = *line, *strend;
+    char *res;
+    char quote;
+    int count = 1;
+
+    while (apr_isspace(*str))
+        ++str;
+
+    if (!*str) {
+        *line = str;
+        return "";
+    }
+
+    if ((quote = *str) == '"' || quote == '\'')
+        return ap_getword_conf(p, line);
+
+    if (quote == '{') {
+        strend = str + 1;
+        while (*strend) {
+            if (*strend == '}' && !--count)
+                break;
+            if (*strend == '{')
+                ++count;
+            if (*strend == '\\' && strend[1] && strend[1] == '\\') {
+                ++strend;
+            }
+            ++strend;
+        }
+        res = substring_conf(p, str + 1, strend - str - 1, 0);
+
+        if (*strend == '}')
+            ++strend;
+    }
+    else {
+        strend = str;
+        while (*strend && !apr_isspace(*strend))
+            ++strend;
+
+        res = substring_conf(p, str, strend - str, 0);
+    }
+
+    while (apr_isspace(*strend))
+        ++strend;
+    *line = strend;
+    return res;
+}
+
 AP_DECLARE(int) ap_cfg_closefile(ap_configfile_t *cfp)
 {
 #ifdef DEBUG
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL, APLOGNO(00551)
         "Done with config file %s", cfp->name);
 #endif
