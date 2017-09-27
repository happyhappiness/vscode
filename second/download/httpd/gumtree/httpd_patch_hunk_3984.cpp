             }
             ap_destroy_sub_req(rr);
             break;
 
         case TOKEN_RE:
             if (!error) {
-                error = "No operator before regex in expr \"%s\" in file %s";
+                error = APLOGNO(03190) "No operator before regex in expr \"%s\" in file %s";
             }
         case TOKEN_LBRACE:
             if (!error) {
-                error = "Unmatched '(' in \"%s\" in file %s";
+                error = APLOGNO(03191) "Unmatched '(' in \"%s\" in file %s";
             }
         default:
             if (!error) {
-                error = "internal parser error in \"%s\" in file %s";
+                error = APLOGNO(03192) "internal parser error in \"%s\" in file %s";
             }
 
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, error, expr,r->filename);
+            /* Intentional no APLOGNO */
+            /* error text provides APLOGNO */
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, error, expr, r->filename);
             *was_error = 1;
             return 0;
         }
 
         DEBUG_DUMP_EVAL(ctx, current);
         current->done = 1;
