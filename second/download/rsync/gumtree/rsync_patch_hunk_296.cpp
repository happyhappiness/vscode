   }
 
   strncpy(fname,dir,MAXPATHLEN-1);
   fname[MAXPATHLEN-1]=0;
   l = strlen(fname);
   if (fname[l-1] != '/') {
+        if (l == MAXPATHLEN-1) {
+              fprintf(FERROR,"skipping long-named directory %s\n",fname);
+              closedir(d);
+              return;
+        }
 	  strcat(fname,"/");
 	  l++;
   }
   p = fname + strlen(fname);
 
   if (cvs_exclude) {
-    strcpy(p,".cvsignore");
-    local_exclude_list = make_exclude_list(fname,NULL,0);
+    if (strlen(fname) + strlen(".cvsignore") <= MAXPATHLEN-1) {
+      strcpy(p,".cvsignore");
+      local_exclude_list = make_exclude_list(fname,NULL,0);
+    } else {
+      fprintf(FERROR,"cannot cvs-exclude in long-named directory %s\n",fname);
+    }
   }  
 
   for (di=readdir(d); di; di=readdir(d)) {
     if (strcmp(di->d_name,".")==0 ||
 	strcmp(di->d_name,"..")==0)
       continue;
