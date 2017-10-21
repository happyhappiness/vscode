       file = &flist->files[i];
 
       fname[0] = 0;
       if (file->dir) {
 	strncpy(fname,file->dir,MAXPATHLEN-1);
 	fname[MAXPATHLEN-1] = 0;
+      if (strlen(fname) == MAXPATHLEN-1) {
+        fprintf(FERROR, "send_files failed on long-named directory %s\n",
+                fname);
+        return -1;
+      }
 	strcat(fname,"/");
       }
       strncat(fname,file->name,MAXPATHLEN-strlen(fname));
 
       if (verbose > 2) 
 	fprintf(FERROR,"send_files(%d,%s)\n",i,fname);
