         }

         /* Trigger an AOF rewrite if needed */
         printf("%d\n", server.auto_aofrewrite_perc);
         if (server.auto_aofrewrite_perc &&
             server.appendonly_current_size > server.auto_aofrewrite_min_size)
         {
