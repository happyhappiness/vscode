   }
 
   if (!*list || !((*list)[len] = strdup(pattern)))
     out_of_memory("add_exclude");
 
   if (verbose > 2)
-    fprintf(FINFO,"add_exclude(%s)\n",pattern);
+    rprintf(FINFO,"add_exclude(%s)\n",pattern);
   
   (*list)[len+1] = NULL;
 }
 
 void add_exclude(char *pattern)
 {
