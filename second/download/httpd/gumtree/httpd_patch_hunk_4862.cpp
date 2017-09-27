             break;
         }
         if (first) {
             apr_file_puts("%stdout\n", f);
             first = 0;
         }
-        apr_file_write(f, buf, &len);
+        apr_file_write_full(f, buf, len, NULL);
         apr_file_puts("\n", f);
     }
 
     if (script_err) {
         if (apr_file_gets(argsbuffer, HUGE_STRING_LEN,
                           script_err) == APR_SUCCESS) {
