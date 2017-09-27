         retained = ap_retained_data_create(userdata_key, sizeof(*retained));
         retained->max_daemons_limit = -1;
         retained->idle_spawn_rate = 1;
     }
     ++retained->module_loads;
     if (retained->module_loads == 2) {
-        int i;
-        static apr_uint32_t foo = 0;
+        /* test for correct operation of fdqueue */
+        static apr_uint32_t foo1, foo2;
 
-        apr_atomic_inc32(&foo);
-        apr_atomic_dec32(&foo);
-        apr_atomic_dec32(&foo);
-        i = apr_atomic_dec32(&foo);
-        if (i >= 0) {
+        apr_atomic_set32(&foo1, 100);
+        foo2 = apr_atomic_add32(&foo1, -10);
+        if (foo2 != 100 || foo1 != 90) {
             ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL, APLOGNO(02405)
-                         "atomics not working as expected");
+                         "atomics not working as expected - add32 of negative number");
             return HTTP_INTERNAL_SERVER_ERROR;
         }
         rv = apr_pollset_create(&event_pollset, 1, plog,
                                 APR_POLLSET_THREADSAFE | APR_POLLSET_NOCOPY);
         if (rv != APR_SUCCESS) {
             ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL, APLOGNO(00495)
