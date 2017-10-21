   if (!flist->files) out_of_memory("send_file_list");
 
   for (i=0;i<argc;i++) {
     char fname2[MAXPATHLEN];
     char *fname = fname2;
 
-    strcpy(fname,argv[i]);
+    strncpy(fname,argv[i],MAXPATHLEN-1);
+    fname[MAXPATHLEN-1] = 0;
 
     l = strlen(fname);
     if (l != 1 && fname[l-1] == '/') {
       strcat(fname,".");
     }
 
