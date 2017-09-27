 /* simple little function to write an error string and exit */
 
 static void err(char *s)
 {
     fprintf(stderr, "%s\n", s);
     if (done)
-        printf("Total of %ld requests completed\n" , done);
+        printf("Total of %d requests completed\n" , done);
     exit(1);
 }
 
 /* simple little function to write an APR error string and exit */
 
 static void apr_err(char *s, apr_status_t rv)
