                                                    desc_width), r);
                 }
             }
             ap_rputc('\n', r);
         }
         else {
-            ap_rvputs(r, "<li><a href=\"", anchor, "\"> ", t2,
-                         "</a></li>\n", NULL);
+            ap_rvputs(r, "<li><a href=\"", anchor, "\"> ",
+                      ap_escape_html(scratch, t2),
+                      "</a></li>\n", NULL);
         }
     }
     if (autoindex_opts & TABLE_INDEXING) {
         ap_rvputs(r, breakrow, "</table>\n", NULL);
     }
     else if (autoindex_opts & FANCY_INDEXING) {
