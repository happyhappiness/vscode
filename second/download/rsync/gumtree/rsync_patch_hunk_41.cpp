     }
     recv_generator(local_name?local_name:flist->files[i].name,
 		   flist,i,f);
   }
   write_int(f,-1);
   write_flush(f);
-  if (verbose > 1)
+  if (verbose > 2)
     fprintf(stderr,"generator wrote %d\n",write_total());
 }
