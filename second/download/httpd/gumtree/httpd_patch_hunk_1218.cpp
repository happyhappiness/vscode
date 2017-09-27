 static apr_status_t freetds_term(void *dummy)
 {
     dbexit();
     regfree(&dbd_freetds_find_arg);
     return APR_SUCCESS;
 }
+static int freetds_err_handler(DBPROCESS *dbproc, int severity, int dberr,
+                               int oserr, char *dberrstr, char *oserrstr)
+{
+    return INT_CANCEL; /* never exit */
+}
 static void dbd_freetds_init(apr_pool_t *pool)
 {
     int rv = regcomp(&dbd_freetds_find_arg,
                      "%(\\{[^}]*\\})?([0-9]*)[A-Za-z]", REG_EXTENDED);
     if (rv != 0) {
         char errmsg[256];
         regerror(rv, &dbd_freetds_find_arg, errmsg, 256);
         fprintf(stderr, "regcomp failed: %s\n", errmsg);
     }
     dbinit();
+    dberrhandle(freetds_err_handler);
     apr_pool_cleanup_register(pool, NULL, freetds_term, apr_pool_cleanup_null);
 }
 
 #ifdef COMPILE_STUBS
 /* get_name is the only one of these that is implemented */
 static const char *dbd_freetds_get_name(const apr_dbd_results_t *res, int n)
