 
   phase++;
   csum_length = SUM_LENGTH;
   ignore_times=1;
 
   if (verbose > 2)
-    fprintf(FINFO,"generate_files phase=%d\n",phase);
+    rprintf(FINFO,"generate_files phase=%d\n",phase);
 
   write_int(f,-1);
   write_flush(f);
 
   /* we expect to just sit around now, so don't exit on a timeout. If we
      really get a timeout then the other process should exit */
