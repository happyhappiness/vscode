     if (rv != APR_SUCCESS) {
         fprintf(stderr, "ab: Could not read POST data file: %s\n",
                 apr_strerror(rv, errmsg, sizeof errmsg));
         return rv;
     }
     apr_file_close(postfd);
-    return 0;
+    return APR_SUCCESS;
 }
 
 /* ------------------------------------------------------- */
 
 /* sort out command-line args and call test */
 int main(int argc, const char * const argv[])
 {
-    int r, l;
+    int l;
     char tmp[1024];
     apr_status_t status;
     apr_getopt_t *opt;
     const char *optarg;
     char c;
 #ifdef USE_SSL
