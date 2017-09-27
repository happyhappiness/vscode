             else {
                 /* Something that isn't a HTTP request, unless some future
                  * edition defines new transfer encodings, is unsupported.
                  */
                 ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r,
                               "Unknown Transfer-Encoding: %s", tenc);
-                return bail_out_on_error(ctx, f, HTTP_NOT_IMPLEMENTED);
+                return bail_out_on_error(ctx, f, HTTP_BAD_REQUEST);
             }
             lenp = NULL;
         }
         if (lenp) {
             char *endstr;
 
