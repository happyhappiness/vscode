     status_code = RET_OKAY;
   }
 
   printf("%s: %lf percent |", status_str, percentage);
   for (size_t i = 0; i < values_num; i++)
     printf(" %s=%lf;;;;", values_names[i], values[i]);
-  return (status_code);
+  return status_code;
 } /* int do_check_con_percentage */
 
 static int do_check(lcc_connection_t *connection) {
   gauge_t *values;
   char **values_names;
   size_t values_num;
