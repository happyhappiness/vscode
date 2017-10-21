 	rprintf(FINFO, "\n");
 }
 
 
 void out_of_memory(char *str)
 {
-  rprintf(FERROR,"ERROR: out of memory in %s\n",str);
-  exit_cleanup(RERR_MALLOC);
+	rprintf(FERROR, "ERROR: out of memory in %s\n", str);
+	exit_cleanup(RERR_MALLOC);
 }
 
 void overflow(char *str)
 {
-  rprintf(FERROR,"ERROR: buffer overflow in %s\n",str);
-  exit_cleanup(RERR_MALLOC);
+	rprintf(FERROR, "ERROR: buffer overflow in %s\n", str);
+	exit_cleanup(RERR_MALLOC);
 }
 
 
 
 int set_modtime(char *fname, time_t modtime)
 {
