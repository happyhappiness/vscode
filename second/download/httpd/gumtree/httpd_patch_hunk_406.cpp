 
     apr_file_printf(f, "\n");
 }
 
 static void usage(void)
 {
-    fprintf(stderr, "Usage: htdigest [-c] passwordfile realm username\n");
-    fprintf(stderr, "The -c flag creates a new file.\n");
+    apr_file_printf(errfile, "Usage: htdigest [-c] passwordfile realm username\n");
+    apr_file_printf(errfile, "The -c flag creates a new file.\n");
     exit(1);
 }
 
 static void interrupted(void)
 {
-    fprintf(stderr, "Interrupted.\n");
+    apr_file_printf(errfile, "Interrupted.\n");
     cleanup_tempfile_and_exit(1);
 }
 
 static void terminate(void)
 {
+    apr_terminate();
 #ifdef NETWARE
     pressanykey();
 #endif
-    apr_terminate();
 }
 
 int main(int argc, const char * const argv[])
 {
     apr_file_t *f;
     apr_status_t rv;
     char tn[] = "htdigest.tmp.XXXXXX";
+    char *dirname;
     char user[MAX_STRING_LEN];
     char realm[MAX_STRING_LEN];
     char line[MAX_STRING_LEN];
     char l[MAX_STRING_LEN];
     char w[MAX_STRING_LEN];
     char x[MAX_STRING_LEN];
-    char command[MAX_STRING_LEN];
     int found;
    
     apr_app_initialize(&argc, &argv, NULL);
     atexit(terminate); 
     apr_pool_create(&cntxt, NULL);
+    apr_file_open_stderr(&errfile, cntxt);
 
 #if APR_CHARSET_EBCDIC
     rv = apr_xlate_open(&to_ascii, "ISO8859-1", APR_DEFAULT_CHARSET, cntxt);
     if (rv) {
-        fprintf(stderr, "apr_xlate_open(): %s (%d)\n",
+        apr_file_printf(errfile, "apr_xlate_open(): %s (%d)\n",
                 apr_strerror(rv, line, sizeof(line)), rv);
         exit(1);
     }
 #endif
     
     apr_signal(SIGINT, (void (*)(int)) interrupted);
