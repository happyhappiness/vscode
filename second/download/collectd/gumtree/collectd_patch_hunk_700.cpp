   } else if (*endptr != 0) {
     fprintf(stderr, "Garbage after end of value: \"%s\"\n", str);
     exit(EXIT_FAILURE);
   }
 
   *ret_value = tmp;
-  return (0);
+  return 0;
 } /* }}} int get_double_opt */
 
 static int read_options(int argc, char **argv) /* {{{ */
 {
   int opt;
 
