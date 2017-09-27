 }
 static void lua_insert_filter_harness(request_rec *r)
 {
     /* ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, "LuaHookInsertFilter not yet implemented"); */
 }
 
+static int lua_log_transaction_harness(request_rec *r)
+{
+    return lua_request_rec_hook_harness(r, "log_transaction", APR_HOOK_FIRST);
+}
+
 static int lua_quick_harness(request_rec *r, int lookup)
 {
     if (lookup) {
         return DECLINED;
     }
     return lua_request_rec_hook_harness(r, "quick", APR_HOOK_MIDDLE);
