   status = lcc_network_values_send(net, vl);
   if (status != 0)
     fprintf(stderr, "lcc_network_values_send failed with status %i.\n", status);
 
   vl->time += vl->interval;
 
-  return (0);
+  return 0;
 } /* }}} int send_value */
 
 static int get_integer_opt(const char *str, int *ret_value) /* {{{ */
 {
   char *endptr;
   int tmp;
