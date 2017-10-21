     return;
   }
 
   if (statret == -1) {
     if (errno == ENOENT) {
       write_int(f_out,i);
-      send_sums(NULL,f_out);
+      if (!dry_run) send_sums(NULL,f_out);
     } else {
       if (verbose > 1)
 	fprintf(stderr,"recv_generator failed to open %s\n",fname);
     }
     return;
   }
