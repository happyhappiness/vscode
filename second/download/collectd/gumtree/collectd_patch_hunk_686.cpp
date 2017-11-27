     /* skip over the (empty) hostname and following '/' */
     printf("\t%s\n", id + 1);
   }
 
   free(ret_ident);
   free(hostname);
-  return (RET_OKAY);
+  return RET_OKAY;
 } /* int do_listval */
 
 static int do_check_con_none(size_t values_num, double *values,
                              char **values_names) {
   int num_critical = 0;
   int num_warning = 0;
