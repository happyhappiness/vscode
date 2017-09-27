 
             if (thisinfo.filetype == APR_LNK) {
                 /* Is this a possibly acceptable symlink?
                  */
                 if ((res = resolve_symlink(r->filename, &thisinfo,
                                            opts.opts, r->pool)) != OK) {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00037)
                                   "Symbolic link not allowed "
                                   "or link target not accessible: %s",
                                   r->filename);
                     return r->status = res;
                 }
             }
