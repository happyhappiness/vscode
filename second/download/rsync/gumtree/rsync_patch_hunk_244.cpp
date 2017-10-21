   if (!d) {
     fprintf(FERROR,"%s: %s\n",
 	    dir,strerror(errno));
     return;
   }
 
-  strcpy(fname,dir);
+  strncpy(fname,dir,MAXPATHLEN-1);
+  fname[MAXPATHLEN-1]=0;
   l = strlen(fname);
-  if (fname[l-1] != '/')
-    strcat(fname,"/");
+  if (fname[l-1] != '/') {
+	  strcat(fname,"/");
+	  l++;
+  }
   p = fname + strlen(fname);
 
   if (cvs_exclude) {
     strcpy(p,".cvsignore");
     local_exclude_list = make_exclude_list(fname,NULL,0);
   }  
 
   for (di=readdir(d); di; di=readdir(d)) {
     if (strcmp(di->d_name,".")==0 ||
 	strcmp(di->d_name,"..")==0)
       continue;
-    strcpy(p,di->d_name);
+    strncpy(p,di->d_name,MAXPATHLEN-(l+1));
     send_file_name(f,flist,fname);
   }
 
   closedir(d);
 }
 
