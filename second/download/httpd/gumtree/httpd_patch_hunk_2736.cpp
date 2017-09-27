 
             cgi_pfn_ps(ctx, tag_val, parsed_string, sizeof(parsed_string),
                        SSI_EXPAND_DROP_NAME);
 
             rv = include_cgi(ctx, f, bb, parsed_string);
             if (rv != APR_SUCCESS) {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "invalid CGI ref "
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01230) "invalid CGI ref "
                               "\"%s\" in %s", tag_val, file);
                 SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                 break;
             }
         }
         else {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter "
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01231) "unknown parameter "
                           "\"%s\" to tag exec in %s", tag, file);
             SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
             break;
         }
     }
 
