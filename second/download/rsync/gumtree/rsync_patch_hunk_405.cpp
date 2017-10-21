     if (S_ISREG(flist->files[i]->mode))
       total_size += flist->files[i]->length;
 
     flist->count++;
 
     if (verbose > 2)
-      fprintf(FINFO,"recv_file_name(%s)\n",f_name(flist->files[i]));
+      rprintf(FINFO,"recv_file_name(%s)\n",f_name(flist->files[i]));
   }
 
 
   if (verbose > 2)
-    fprintf(FINFO,"received %d names\n",flist->count);
+    rprintf(FINFO,"received %d names\n",flist->count);
 
   clean_flist(flist);
 
   if (verbose && recurse && !am_server) {
-    fprintf(FINFO,"done\n");
+    rprintf(FINFO,"done\n");
   }
 
   /* now recv the uid/gid list. This was introduced in protocol version 15 */
   if (f != -1 && remote_version >= 15) {
 	  recv_uid_list(f, flist);
   }
