  * Various utility functions which are common to a whole lot of
  * script-type extensions mechanisms, and might as well be gathered
  * in one place (if only to avoid creating inter-module dependancies
  * where there don't have to be).
  */
 
-#define MALFORMED_MESSAGE "malformed header from script. Bad header="
-#define MALFORMED_HEADER_LENGTH_TO_SHOW 30
+/* we know core's module_index is 0 */
+#undef APLOG_MODULE_INDEX
+#define APLOG_MODULE_INDEX AP_CORE_MODULE_INDEX
 
-APLOG_USE_MODULE(core);
-
-static char *http2env(apr_pool_t *a, const char *w)
+static char *http2env(request_rec *r, const char *w)
 {
-    char *res = (char *)apr_palloc(a, sizeof("HTTP_") + strlen(w));
+    char *res = (char *)apr_palloc(r->pool, sizeof("HTTP_") + strlen(w));
     char *cp = res;
     char c;
 
     *cp++ = 'H';
     *cp++ = 'T';
     *cp++ = 'T';
     *cp++ = 'P';
     *cp++ = '_';
 
     while ((c = *w++) != 0) {
-        if (!apr_isalnum(c)) {
+        if (apr_isalnum(c)) {
+            *cp++ = apr_toupper(c);
+        }
+        else if (c == '-') {
             *cp++ = '_';
         }
         else {
-            *cp++ = apr_toupper(c);
+            ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
+                          "Not exporting header with invalid name as envvar: %s",
+                          ap_escape_logitem(r->pool, w));
+            return NULL;
         }
     }
     *cp = 0;
 
     return res;
 }
 
+static void add_unless_null(apr_table_t *table, const char *name, const char *val)
+{
+    if (name && val) {
+        apr_table_addn(table, name, val);
+    }
+}
+
+static void env2env(apr_table_t *table, const char *name)
+{
+    add_unless_null(table, name, getenv(name));
+}
+
 AP_DECLARE(char **) ap_create_environment(apr_pool_t *p, apr_table_t *t)
 {
     const apr_array_header_t *env_arr = apr_table_elts(t);
     const apr_table_entry_t *elts = (const apr_table_entry_t *) env_arr->elts;
     char **env = (char **) apr_palloc(p, (env_arr->nelts + 2) * sizeof(char *));
     int i, j;
