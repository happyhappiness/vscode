 /*
  * Process the tags in the format string. Tags may be format specifiers
  * (%D, %t, etc.), whitespace or text strings. For each tag, run the handler
  * (formatter) specific to the tag. Handlers return text strings.
  * Concatenate the return from each handler into one string that is
  * returned from this call.
+ * If the original value was prefixed with "expr=", processing is
+ * handled instead by ap_expr.
  */
 static char* process_tags(header_entry *hdr, request_rec *r)
 {
     int i;
     const char *s;
     char *str = NULL;
+    format_tag *tag = NULL;
+
+    if (hdr->expr_out) { 
+        const char *err;
+        const char *val;
+        val = ap_expr_str_exec(r, hdr->expr_out, &err);
+        if (err) { 
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02557)
+                          "Can't evaluate value expression: %s", err);
+            return "";
+        }
+        return apr_pstrdup(r->pool, val);
+    }
 
-    format_tag *tag = (format_tag*) hdr->ta->elts;
+    tag = (format_tag*) hdr->ta->elts;
 
     for (i = 0; i < hdr->ta->nelts; i++) {
         s = tag[i].func(r, tag[i].arg);
         if (str == NULL)
             str = apr_pstrdup(r->pool, s);
         else
