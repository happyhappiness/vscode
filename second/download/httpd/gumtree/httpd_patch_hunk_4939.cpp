 
         while (*c && !apr_isspace(*c)) {
             ++c;
         }
 
         dbmval.dptr = apr_pstrmemdup(p, value,  c - value);
-        dbmval.dsize = (c - line);
+        dbmval.dsize = (c - value);
 
         if (verbose) {
             apr_file_printf(errfile, "    '%s' -> '%s'"NL,
                             dbmkey.dptr, dbmval.dptr);
         }
 
