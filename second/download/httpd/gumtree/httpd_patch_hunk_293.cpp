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
 
             ++cols;
