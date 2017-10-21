       recv_generator(local_name?local_name:f_name(file),
 		     flist,i,f);    
     }
 
     phase++;
     if (verbose > 2)
-      fprintf(FINFO,"generate_files phase=%d\n",phase);
+      rprintf(FINFO,"generate_files phase=%d\n",phase);
 
     write_int(f,-1);
     write_flush(f);
   }
 
 
   if (verbose > 2)
-    fprintf(FINFO,"generator wrote %ld\n",(long)write_total());
+    rprintf(FINFO,"generator wrote %ld\n",(long)write_total());
 }
 
 
