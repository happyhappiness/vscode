  * This routine puts the standard HTML header at the top of the index page.
  * We include the DOCTYPE because we may be using features therefrom (i.e.,
  * HEIGHT and WIDTH attributes on the icons if we're FancyIndexing).
  */
 static void emit_preamble(request_rec *r, int xhtml, const char *title)
 {
+    autoindex_config_rec *d;
+
+    d = (autoindex_config_rec *) ap_get_module_config(r->per_dir_config,
+                                                      &autoindex_module);
+
     ap_rvputs(r, xhtml ? DOCTYPE_XHTML_1_0T : DOCTYPE_HTML_3_2,
               "<html>\n <head>\n  <title>Index of ", title,
-              "</title>\n </head>\n <body>\n", NULL);
+              "</title>\n", NULL);
+    if (d->style_sheet != NULL) {
+        ap_rvputs(r, "  <link rel=\"stylesheet\" href=\"", d->style_sheet,
+                "\" type=\"text/css\"", xhtml ? " />\n" : ">\n", NULL);
+    }
+    ap_rvputs(r, " </head>\n <body>\n", NULL);
 }
 
 static void push_item(apr_array_header_t *arr, char *type, const char *to,
                       const char *path, const char *data)
 {
     struct item *p = (struct item *) apr_array_push(arr);
