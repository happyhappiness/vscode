     apr_terminate();
 #ifdef NETWARE
     pressanykey();
 #endif
 }
 
-static void check_args(apr_pool_t *pool, int argc, const char *const argv[],
-                       int *alg, int *mask, char **user, char **pwfilename,
-                       char **password)
+static void check_args(int argc, const char *const argv[],
+                       struct passwd_ctx *ctx, int *mask, char **user,
+                       char **pwfilename)
 {
     const char *arg;
     int args_left = 2;
-    int i;
+    int i, ret;
+    apr_getopt_t *state;
+    apr_status_t rv;
+    char opt;
+    const char *opt_arg;
+    apr_pool_t *pool = ctx->pool;
 
-    /*
-     * Preliminary check to make sure they provided at least
-     * three arguments, we'll do better argument checking as
-     * we parse the command line.
-     */
-    if (argc < 3) {
-        usage();
-    }
+    rv = apr_getopt_init(&state, pool, argc, argv);
+    if (rv != APR_SUCCESS)
+        exit(ERR_SYNTAX);
 
-    /*
-     * Go through the argument list and pick out any options.  They
-     * have to precede any other arguments.
-     */
-    for (i = 1; i < argc; i++) {
-        arg = argv[i];
-        if (*arg != '-') {
+    while ((rv = apr_getopt(state, "cnmspdBbDiC:", &opt, &opt_arg)) == APR_SUCCESS) {
+        switch (opt) {
+        case 'c':
+            *mask |= APHTP_NEWFILE;
             break;
-        }
-        while (*++arg != '\0') {
-            if (*arg == 'c') {
-                *mask |= APHTP_NEWFILE;
-            }
-            else if (*arg == 'n') {
-                *mask |= APHTP_NOFILE;
-                args_left--;
-            }
-            else if (*arg == 'm') {
-                *alg = ALG_APMD5;
-            }
-            else if (*arg == 's') {
-                *alg = ALG_APSHA;
-            }
-            else if (*arg == 'p') {
-                *alg = ALG_PLAIN;
-            }
-            else if (*arg == 'd') {
-                *alg = ALG_CRYPT;
-            }
-            else if (*arg == 'b') {
-                *mask |= APHTP_NONINTERACTIVE;
-                args_left++;
-            }
-            else if (*arg == 'D') {
-                *mask |= APHTP_DELUSER;
-            }
-            else {
-                usage();
+        case 'n':
+            args_left--;
+            *mask |= APHTP_NOFILE;
+            break;
+        case 'D':
+            *mask |= APHTP_DELUSER;
+            break;
+        default:
+            ret = parse_common_options(ctx, opt, opt_arg);
+            if (ret) {
+                apr_file_printf(errfile, "%s: %s" NL, argv[0], ctx->errstr);
+                exit(ret);
             }
         }
     }
+    if (ctx->passwd_src == PW_ARG)
+        args_left++;
+    if (rv != APR_EOF)
+        usage();
 
     if ((*mask & APHTP_NEWFILE) && (*mask & APHTP_NOFILE)) {
         apr_file_printf(errfile, "%s: -c and -n options conflict" NL, argv[0]);
         exit(ERR_SYNTAX);
     }
     if ((*mask & APHTP_NEWFILE) && (*mask & APHTP_DELUSER)) {
