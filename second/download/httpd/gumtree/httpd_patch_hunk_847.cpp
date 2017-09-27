         }
         if (i != SERVER_DEAD)
             total+=status_array[i];
     }
     printf ("Total Running:\t%d\tout of: \t%d\n", total, ap_threads_limit);
     printf ("Requests per interval:\t%d\n", reqs);
-    
+
 #ifdef DBINFO_ON
     printf ("Would blocks:\t%d\n", wblock);
     printf ("Successful retries:\t%d\n", retry_success);
     printf ("Failed retries:\t%d\n", retry_fail);
     printf ("Avg retries:\t%d\n", retry_success == 0 ? 0 : avg_retries / retry_success);
 #endif
