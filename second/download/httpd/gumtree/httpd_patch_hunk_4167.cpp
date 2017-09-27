             printf ("\rShutdown pending. Waiting for %lu thread(s) to terminate...",
                     worker_thread_count);
             apr_thread_yield();
         }
 
         mpm_main_cleanup();
-        return 1;
+        return DONE;
     }
     else {  /* the only other way out is a restart */
         /* advance to the next generation */
         /* XXX: we really need to make sure this new generation number isn't in
          * use by any of the children.
          */
