                 if (d->icon_width) {
                     ap_rprintf(r, " width=\"%d\"", d->icon_width);
                 }
                 if (d->icon_height) {
                     ap_rprintf(r, " height=\"%d\"", d->icon_height);
                 }
-                ap_rputs(" /></th>", r);
+
+                if (autoindex_opts & EMIT_XHTML) {
+                    ap_rputs(" /", r);
+                }
+                ap_rputs("></th>", r);
             }
             else {
                 ap_rputs("&nbsp;</th>", r);
             }
-            
+
             ++cols;
         }
         ap_rputs("<th>", r);
-        emit_link(r, "Name", K_NAME, keyid, direction, 
+        emit_link(r, "Name", K_NAME, keyid, direction,
                   colargs, static_columns);
         if (!(autoindex_opts & SUPPRESS_LAST_MOD)) {
             ap_rputs("</th><th>", r);
-            emit_link(r, "Last modified", K_LAST_MOD, keyid, direction, 
+            emit_link(r, "Last modified", K_LAST_MOD, keyid, direction,
                       colargs, static_columns);
             ++cols;
         }
         if (!(autoindex_opts & SUPPRESS_SIZE)) {
             ap_rputs("</th><th>", r);
-            emit_link(r, "Size", K_SIZE, keyid, direction, 
+            emit_link(r, "Size", K_SIZE, keyid, direction,
                       colargs, static_columns);
             ++cols;
         }
         if (!(autoindex_opts & SUPPRESS_DESC)) {
             ap_rputs("</th><th>", r);
-            emit_link(r, "Description", K_DESC, keyid, direction, 
+            emit_link(r, "Description", K_DESC, keyid, direction,
                       colargs, static_columns);
             ++cols;
         }
         if (!(autoindex_opts & SUPPRESS_RULES)) {
             breakrow = apr_psprintf(r->pool,
                                     "<tr><th colspan=\"%d\">"
-                                    "<hr /></th></tr>\n", cols);
+                                    "<hr%s></th></tr>\n", cols,
+                                    (autoindex_opts & EMIT_XHTML) ? " /" : "");
         }
         ap_rvputs(r, "</th></tr>", breakrow, NULL);
     }
     else if (autoindex_opts & FANCY_INDEXING) {
         ap_rputs("<pre>", r);
         if (!(autoindex_opts & SUPPRESS_ICON)) {
