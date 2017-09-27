             if (thisinfo.filetype == APR_LNK) {
                 /* Is this a possibly acceptable symlink?
                  */
                 if ((res = resolve_symlink(r->filename, &thisinfo,
                                            opts.opts, r->pool)) != OK) {
                     ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                                  "Symbolic link not allowed: %s",
+                                  "Symbolic link not allowed "
+                                  "or link target not accessible: %s",
                                   r->filename);
                     return r->status = res;
                 }
             }
 
             /* Ok, we are done with the link's info, test the real target
              */
-            if (thisinfo.filetype == APR_REG || 
+            if (thisinfo.filetype == APR_REG ||
                 thisinfo.filetype == APR_NOFILE) {
                 /* That was fun, nothing left for us here
                  */
                 break;
             }
             else if (thisinfo.filetype != APR_DIR) {
