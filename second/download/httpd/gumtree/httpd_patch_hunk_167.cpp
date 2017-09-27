                 else {
                     ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "unknown value \"%s\" to parameter \"encoding\" of "
                            "tag echo in %s", tag_val, r->filename);
                     CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                         *inserted_head);
+                    return 1;
                 }
             }
             else {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                             "unknown parameter \"%s\" in tag echo of %s",
                             tag, r->filename);
                 CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
+                return 1;
             }
 
         }
     }
     return 0;
 }
