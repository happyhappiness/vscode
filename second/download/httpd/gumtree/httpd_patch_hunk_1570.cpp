     pad_scratch = apr_palloc(r->pool, name_width + 1);
     memset(pad_scratch, ' ', name_width);
     pad_scratch[name_width] = '\0';
 
     if (autoindex_opts & TABLE_INDEXING) {
         int cols = 1;
-        ap_rputs("<table><tr>", r);
+        if (d->style_sheet != NULL) {
+            /* Emit table with style id */
+            ap_rputs("  <table id=\"indexlist\">\n   <tr class=\"indexhead\">", r);
+        } else {
+            ap_rputs("  <table>\n   <tr>", r);
+        }
         if (!(autoindex_opts & SUPPRESS_ICON)) {
-            ap_rputs("<th>", r);
+            ap_rvputs(r, "<th", (d->style_sheet != NULL) ? " class=\"indexcolicon\">" : " valign=\"top\">", NULL);
             if ((tp = find_default_icon(d, "^^BLANKICON^^"))) {
                 ap_rvputs(r, "<img src=\"", ap_escape_html(scratch, tp),
                              "\" alt=\"[ICO]\"", NULL);
                 if (d->icon_width) {
                     ap_rprintf(r, " width=\"%d\"", d->icon_width);
                 }
