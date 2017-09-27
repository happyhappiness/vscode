                         ap_rvputs(r, "</td><td>",
                                   terminate_description(d, ar[x]->desc,
                                                         autoindex_opts,
                                                         desc_width), NULL);
                     }
                 }
-            }
-            else {
-                ap_rputs("</td><td>&nbsp;", r);
+                else {
+                    ap_rputs("</td><td>&nbsp;", r);
+                }
             }
             ap_rputs("</td></tr>\n", r);
         }
         else if (autoindex_opts & FANCY_INDEXING) {
             if (!(autoindex_opts & SUPPRESS_ICON)) {
                 if (autoindex_opts & ICONS_ARE_LINKS) {
