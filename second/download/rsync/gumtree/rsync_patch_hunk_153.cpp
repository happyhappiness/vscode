       args[argc++] = path;
   }
 
   args[argc] = NULL;
 
   if (verbose > 3) {
-    fprintf(stderr,"cmd=");
+    fprintf(FERROR,"cmd=");
     for (i=0;i<argc;i++)
-      fprintf(stderr,"%s ",args[i]);
-    fprintf(stderr,"\n");
+      fprintf(FERROR,"%s ",args[i]);
+    fprintf(FERROR,"\n");
   }
 
   return piped_child(args,f_in,f_out);
 
 oom:
   out_of_memory("do_cmd");
