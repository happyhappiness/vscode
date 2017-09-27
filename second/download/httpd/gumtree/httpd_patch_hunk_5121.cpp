             SANE("the total time", meantot, mediantot, sdtot);
         }
         else {
             printf("              min   avg   max\n");
 #define CONF_FMT_STRING "%5" APR_TIME_T_FMT " %5" APR_TIME_T_FMT "%5" APR_TIME_T_FMT "\n"
             printf("Connect:    " CONF_FMT_STRING, mincon, meancon, maxcon);
-            printf("Processing: " CONF_FMT_STRING, mintot - mincon,
-                                                   meantot - meancon,
-                                                   maxtot - maxcon);
+            printf("Processing: " CONF_FMT_STRING, mind, meand, maxd);
+            printf("Waiting:    " CONF_FMT_STRING, minwait, meanwait, maxwait);
             printf("Total:      " CONF_FMT_STRING, mintot, meantot, maxtot);
 #undef CONF_FMT_STRING
         }
 
 
         /* Sorted on total connect times */
