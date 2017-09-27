         }
         else {
             t2 = t;
         }
 
         if (autoindex_opts & TABLE_INDEXING) {
-            ap_rputs("<tr>", r);
+            /* Even/Odd rows for IndexStyleSheet */
+            if (d->style_sheet != NULL) {
+                if (ar[x]->alt && (autoindex_opts & ADDALTCLASS)) {
+                    /* Include alt text in class name, distinguish between odd and even rows */
+                    char *altclass = apr_pstrdup(scratch, ar[x]->alt);
+                    ap_str_tolower(altclass);
+                    ap_rvputs(r, "   <tr class=\"", ( x & 0x1) ? "odd-" : "even-", altclass, "\">", NULL);
+                } else {
+                    /* Distinguish between odd and even rows */
+                    ap_rvputs(r, "   <tr class=\"", ( x & 0x1) ? "odd" : "even", "\">", NULL);
+                }
+            } else {
+                ap_rputs("<tr>", r);
+            }
+
             if (!(autoindex_opts & SUPPRESS_ICON)) {
-                ap_rputs("<td valign=\"top\">", r);
+                ap_rvputs(r, "<td", (d->style_sheet != NULL) ? " class=\"indexcolicon\">" : " valign=\"top\">", NULL);
                 if (autoindex_opts & ICONS_ARE_LINKS) {
                     ap_rvputs(r, "<a href=\"", anchor, "\">", NULL);
                 }
                 if ((ar[x]->icon) || d->default_icon) {
                     ap_rvputs(r, "<img src=\"",
                               ap_escape_html(scratch,
