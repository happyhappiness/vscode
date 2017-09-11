@@ -3268,7 +3268,6 @@ void clusterCron(void) {
          * the orphaned masters. Note that it does not make sense to try
          * a migration if there is no master with at least *two* working
          * slaves. */
-        if (orphaned_masters) serverLog(LL_WARNING,"0");
         if (orphaned_masters && max_slaves >= 2 && this_slaves == max_slaves)
             clusterHandleSlaveMigration(max_slaves);
     }