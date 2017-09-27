         char *badchar;
         char *replacement = apr_pstrdup(t->r->pool, val);
         badchar = replacement;
         while ( (badchar = ap_strchr(badchar, '\n')) ) {
             *badchar = ' ';
         }
-        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, t->r, 
-                APLOGNO(02614) "mod_lua: Value for '%s' in table '%s' contains newline!",
+        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, t->r, APLOGNO(02614)
+                      "mod_lua: Value for '%s' in table '%s' contains newline!",
                   key, t->n);
         apr_table_set(t->t, key, replacement);
     }
     else {
         apr_table_set(t->t, key, val);
     }
