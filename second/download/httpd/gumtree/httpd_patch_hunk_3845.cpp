         }
         else {
             ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf, APLOGNO(00146) "%s", msg);
             exit(APEXIT_CHILDFATAL);
         }
     }
+    return APR_SUCCESS;
 }
 
 /* On some architectures it's safe to do unserialized accept()s in the single
  * Listen case.  But it's never safe to do it in the case where there's
  * multiple Listen statements.  Define SINGLE_LISTEN_UNSERIALIZED_ACCEPT
  * when it's safe in the single Listen case.
  */
 #ifdef SINGLE_LISTEN_UNSERIALIZED_ACCEPT
-#define SAFE_ACCEPT(stmt) do {if (ap_listeners->next) {stmt;}} while(0)
+#define SAFE_ACCEPT(stmt) (ap_listeners->next ? (stmt) : APR_SUCCESS)
 #else
-#define SAFE_ACCEPT(stmt) do {stmt;} while(0)
+#define SAFE_ACCEPT(stmt) (stmt)
 #endif
 
 static int prefork_query(int query_code, int *result, apr_status_t *rv)
 {
     *rv = APR_SUCCESS;
     switch(query_code){
