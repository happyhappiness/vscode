         }
 
         dbmval.dptr = apr_pstrmemdup(p, value,  c - value);
         dbmval.dsize = (c - value);
 
         if (verbose) {
-            apr_file_printf(errfile, "    '%s' -> '%s'"NL,
+            apr_file_printf(errfile, "    '%s' -> '%s'" NL,
                             dbmkey.dptr, dbmval.dptr);
         }
 
         rv = apr_dbm_store(dbm, dbmkey, dbmval);
 
         apr_pool_clear(p);
