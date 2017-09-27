         }
         if (!expired) {
             rv = iterator(ctx, s, userctx,
                              (unsigned char *)dbmkey.dptr, dbmkey.dsize,
                              (unsigned char *)dbmval.dptr + sizeof(apr_time_t),
                              dbmval.dsize - sizeof(apr_time_t), pool);
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, s,
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, s, APLOGNO(00816)
                          "dbm `%s' entry iterated", ctx->data_file);
             if (rv != APR_SUCCESS)
                 return rv;
         }
         rv = apr_dbm_nextkey(dbm, &dbmkey);
     }
     apr_dbm_close(dbm);
 
     if (rv != APR_SUCCESS && rv != APR_EOF) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00817)
                      "Failure reading first/next socache DBM file `%s' record",
                      ctx->data_file);
         return rv;
     }
     return APR_SUCCESS;
 }
