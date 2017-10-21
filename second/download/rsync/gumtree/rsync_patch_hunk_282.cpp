     fprintf(FERROR,"cmd=");
     for (i=0;i<argc;i++)
       fprintf(FERROR,"%s ",args[i]);
     fprintf(FERROR,"\n");
   }
 
-  return piped_child(args,f_in,f_out);
+  ret = piped_child(args,f_in,f_out);
+  if (dir) free(dir);
+
+  return ret;
 
 oom:
   out_of_memory("do_cmd");
   return 0; /* not reached */
 }
 
