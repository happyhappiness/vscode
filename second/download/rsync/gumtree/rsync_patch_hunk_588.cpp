 							sizeof(flist->files[0])*
 							flist->malloced);
 	  if (!flist->files)
 		  out_of_memory("send_file_name");
   }
 
+  if (write_batch) /*  dw  */
+    file->flags = FLAG_DELETE;
+
   if (strcmp(file->basename,"")) {
     flist->files[flist->count++] = file;
     send_file_entry(file,f,base_flags);
   }
 
   if (S_ISDIR(file->mode) && recursive) {
