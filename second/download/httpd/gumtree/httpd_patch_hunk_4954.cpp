             else {
                 /* oops, no data out, but not all data read in either, be
                  * safe and stand down to prevent a spin.
                  */
                 ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, f->r, APLOGNO(00766)
                         "cache: Cache provider's store_body returned an "
-                        "empty brigade, but didn't consume all of the"
+                        "empty brigade, but didn't consume all of the "
                         "input brigade, standing down to prevent a spin");
                 ap_remove_output_filter(f);
 
                 /* give someone else the chance to cache the file */
                 cache_remove_lock(conf, cache, f->r, NULL);
 
