  * It returns the substituted string, or NULL on error.
  *
  * Parts of this code are based on Henry Spencer's regsub(), from his
  * AT&T V8 regexp package.
  */
 
-static apr_status_t regsub_core(apr_pool_t *p, char **result,
-                                const char *input,
-                                const char *source, apr_size_t nmatch,
-                                ap_regmatch_t pmatch[], apr_size_t maxlen)
+AP_DECLARE(char *) ap_pregsub(apr_pool_t *p, const char *input,
+                              const char *source, size_t nmatch,
+                              ap_regmatch_t pmatch[])
 {
     const char *src = input;
-    char *dst;
+    char *dest, *dst;
     char c;
-    apr_size_t no;
-    apr_size_t len = 0;
+    size_t no;
+    int len;
 
-    AP_DEBUG_ASSERT(result && p);
-    if (!source || nmatch>AP_MAX_REG_MATCH)
-        return APR_EINVAL;
-    if (!nmatch) {
-        len = strlen(src);
-        if (maxlen > 0 && len >= maxlen)
-            return APR_ENOMEM;
-        *result = apr_pstrmemdup(p, src, len);
-        return APR_SUCCESS;
-    }
+    if (!source)
+        return NULL;
+    if (!nmatch)
+        return apr_pstrdup(p, src);
 
     /* First pass, find the size */
+
+    len = 0;
+
     while ((c = *src++) != '\0') {
-        if (c == '&')
-            no = 0;
-        else if (c == '$' && apr_isdigit(*src))
+        if (c == '$' && apr_isdigit(*src))
             no = *src++ - '0';
         else
-            no = AP_MAX_REG_MATCH;
+            no = 10;
 
-        if (no >= AP_MAX_REG_MATCH) {  /* Ordinary character. */
-            if (c == '\\' && (*src == '$' || *src == '&'))
-                src++;
+        if (no > 9) {                /* Ordinary character. */
+            if (c == '\\' && *src)
+                c = *src++;
             len++;
         }
         else if (no < nmatch && pmatch[no].rm_so < pmatch[no].rm_eo) {
-            if (UTIL_SIZE_MAX - len <= pmatch[no].rm_eo - pmatch[no].rm_so) {
-                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL,
-                             "integer overflow or out of memory condition." );
-                return APR_ENOMEM;
-            }
             len += pmatch[no].rm_eo - pmatch[no].rm_so;
         }
 
     }
 
-    if (len >= maxlen && maxlen > 0)
-        return APR_ENOMEM;
-
-    *result = dst = apr_palloc(p, len + 1);
+    dest = dst = apr_pcalloc(p, len + 1);
 
     /* Now actually fill in the string */
 
     src = input;
 
     while ((c = *src++) != '\0') {
         if (c == '&')
             no = 0;
         else if (c == '$' && apr_isdigit(*src))
             no = *src++ - '0';
         else
-            no = AP_MAX_REG_MATCH;
+            no = 10;
 
-        if (no >= AP_MAX_REG_MATCH) {  /* Ordinary character. */
+        if (no > 9) {                /* Ordinary character. */
             if (c == '\\' && (*src == '$' || *src == '&'))
                 c = *src++;
             *dst++ = c;
         }
         else if (no < nmatch && pmatch[no].rm_so < pmatch[no].rm_eo) {
             len = pmatch[no].rm_eo - pmatch[no].rm_so;
