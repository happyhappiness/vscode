         if (APR_STATUS_IS_ENOENT(retcode)) {
             return DECLINED;
         }
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
             "meta file permissions deny server access: %s", metafilename);
         return HTTP_FORBIDDEN;
-    }
+    };
 
     /* read the headers in */
     rv = scan_meta_file(r, f);
     apr_file_close(f);
 
     return rv;
