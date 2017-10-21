 	if (cvs_exclude) {
 		if (strlen(fname) + strlen(".cvsignore") <= MAXPATHLEN-1) {
 			strcpy(p,".cvsignore");
 			local_exclude_list = make_exclude_list(fname,NULL,0);
 		} else {
 			io_error = 1;
-			fprintf(FINFO,"cannot cvs-exclude in long-named directory %s\n",fname);
+			rprintf(FINFO,"cannot cvs-exclude in long-named directory %s\n",fname);
 		}
 	}  
 	
 	for (di=readdir(d); di; di=readdir(d)) {
-		if (strcmp(di->d_name,".")==0 ||
-		    strcmp(di->d_name,"..")==0)
+		char *dname = d_name(di);
+		if (strcmp(dname,".")==0 ||
+		    strcmp(dname,"..")==0)
 			continue;
-		strncpy(p,di->d_name,MAXPATHLEN-(l+1));
+		strlcpy(p,dname,MAXPATHLEN-(l+1));
 		send_file_name(f,flist,fname,recurse,FLAG_DELETE);
 	}
 
 	closedir(d);
 }
 
 
 
 struct file_list *send_file_list(int f,int argc,char *argv[])
 {
 	int i,l;
-	struct stat st;
+	STRUCT_STAT st;
 	char *p,*dir;
 	char dbuf[MAXPATHLEN];
 	char lastpath[MAXPATHLEN]="";
 	struct file_list *flist;
 
 	if (verbose && recurse && !am_server && f != -1) {
-		fprintf(FINFO,"building file list ... ");
-		fflush(FINFO);
+		rprintf(FINFO,"building file list ... ");
+		rflush(FINFO);
 	}
 
 	flist = (struct file_list *)malloc(sizeof(flist[0]));
 	if (!flist) out_of_memory("send_file_list");
 
 	flist->count=0;
