     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "leaving shmcb_remove_session");
     return res;
 }
 
 
-/* 
+/*
 **
 ** Weirdo cyclic buffer functions
 **
 */
 
 /* This gets used in the cyclic "index array" (in the 'Queue's) and
