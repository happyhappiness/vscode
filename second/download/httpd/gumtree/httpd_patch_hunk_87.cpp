     pad_scratch[name_width] = '\0';
 
     if (autoindex_opts & TABLE_INDEXING) {
         int cols = 1;
         ap_rputs("<table><tr>", r);
         if (!(autoindex_opts & SUPPRESS_ICON)) {
-            ap_rputs("<th title=\"Icon\">", r);
+            ap_rputs("<th>", r);
             if ((tp = find_default_icon(d, "^^BLANKICON^^"))) {
                 ap_rvputs(r, "<img src=\"", ap_escape_html(scratch, tp),
                              "\" alt=\"[ICO]\"", NULL);
                 if (d->icon_width) {
                     ap_rprintf(r, " width=\"%d\"", d->icon_width);
                 }
