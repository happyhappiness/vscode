 
 	return file;
 }
 
 
 
-void send_file_name(int f,struct file_list *flist,char *fname,
-			   int recursive, unsigned base_flags)
+void send_file_name(int f, struct file_list *flist, char *fname,
+		    int recursive, unsigned base_flags)
 {
-  struct file_struct *file;
+	struct file_struct *file;
+
+	file = make_file(f, fname, &flist->string_area, 0);
 
-  file = make_file(f,fname, &flist->string_area, 0);
+	if (!file)
+		return;
+
+	if (show_build_progress_p() & !(flist->count % 100))
+		emit_build_progress(flist);
+
+	flist_expand(flist);
+
+	if (write_batch)	/*  dw  */
+		file->flags = FLAG_DELETE;
 
-  if (!file) return;  
-  
-  if (flist->count >= flist->malloced) {
-	  if (flist->malloced < 1000)
-		  flist->malloced += 1000;
-	  else
-		  flist->malloced *= 2;
-	  flist->files = (struct file_struct **)realloc(flist->files,
-							sizeof(flist->files[0])*
-							flist->malloced);
-	  if (!flist->files)
-		  out_of_memory("send_file_name");
-  }
-
-  if (write_batch) /*  dw  */
-    file->flags = FLAG_DELETE;
-
-  if (strcmp(file->basename,"")) {
-    flist->files[flist->count++] = file;
-    send_file_entry(file,f,base_flags);
-  }
-
-  if (S_ISDIR(file->mode) && recursive) {
-	  struct exclude_struct **last_exclude_list = local_exclude_list;
-	  send_directory(f,flist,f_name(file));
-	  local_exclude_list = last_exclude_list;
-	  return;
-  }
+	if (strcmp(file->basename, "")) {
+		flist->files[flist->count++] = file;
+		send_file_entry(file, f, base_flags);
+	}
+
+	if (S_ISDIR(file->mode) && recursive) {
+		struct exclude_struct **last_exclude_list =
+		    local_exclude_list;
+		send_directory(f, flist, f_name(file));
+		local_exclude_list = last_exclude_list;
+		return;
+	}
 }
 
 
 
-static void send_directory(int f,struct file_list *flist,char *dir)
+static void send_directory(int f, struct file_list *flist, char *dir)
 {
 	DIR *d;
 	struct dirent *di;
 	char fname[MAXPATHLEN];
 	int l;
 	char *p;
 
 	d = opendir(dir);
 	if (!d) {
 		io_error = 1;
-		rprintf(FERROR,"opendir(%s): %s\n",
-			dir,strerror(errno));
+		rprintf(FERROR, "opendir(%s): %s\n", dir, strerror(errno));
 		return;
 	}
 
-	strlcpy(fname,dir,MAXPATHLEN);
+	strlcpy(fname, dir, MAXPATHLEN);
 	l = strlen(fname);
-	if (fname[l-1] != '/') {
-		if (l == MAXPATHLEN-1) {
+	if (fname[l - 1] != '/') {
+		if (l == MAXPATHLEN - 1) {
 			io_error = 1;
-			rprintf(FERROR,"skipping long-named directory %s\n",fname);
+			rprintf(FERROR,
+				"skipping long-named directory %s\n",
+				fname);
 			closedir(d);
 			return;
 		}
-		strlcat(fname,"/", MAXPATHLEN);
+		strlcat(fname, "/", MAXPATHLEN);
 		l++;
 	}
 	p = fname + strlen(fname);
 
 	local_exclude_list = NULL;
 
 	if (cvs_exclude) {
-		if (strlen(fname) + strlen(".cvsignore") <= MAXPATHLEN-1) {
-			strcpy(p,".cvsignore");
-			local_exclude_list = make_exclude_list(fname,NULL,0,0);
+		if (strlen(fname) + strlen(".cvsignore") <= MAXPATHLEN - 1) {
+			strcpy(p, ".cvsignore");
+			local_exclude_list =
+			    make_exclude_list(fname, NULL, 0, 0);
 		} else {
 			io_error = 1;
-			rprintf(FINFO,"cannot cvs-exclude in long-named directory %s\n",fname);
+			rprintf(FINFO,
+				"cannot cvs-exclude in long-named directory %s\n",
+				fname);
 		}
-	}  
-	
-	for (di=readdir(d); di; di=readdir(d)) {
+	}
+
+	for (di = readdir(d); di; di = readdir(d)) {
 		char *dname = d_name(di);
-		if (strcmp(dname,".")==0 ||
-		    strcmp(dname,"..")==0)
+		if (strcmp(dname, ".") == 0 || strcmp(dname, "..") == 0)
 			continue;
-		strlcpy(p,dname,MAXPATHLEN-l);
-		send_file_name(f,flist,fname,recurse,0);
+		strlcpy(p, dname, MAXPATHLEN - l);
+		send_file_name(f, flist, fname, recurse, 0);
 	}
 
 	if (local_exclude_list) {
 		add_exclude_list("!", &local_exclude_list, 0);
 	}
 
 	closedir(d);
 }
 
 
-struct file_list *send_file_list(int f,int argc,char *argv[])
+/*
+ *
+ * I *think* f==-1 means that the list should just be built in memory
+ * and not transmitted.  But who can tell? -- mbp
+ */
+struct file_list *send_file_list(int f, int argc, char *argv[])
 {
-	int i,l;
+	int i, l;
 	STRUCT_STAT st;
-	char *p,*dir,*olddir;
-	char lastpath[MAXPATHLEN]="";
+	char *p, *dir, *olddir;
+	char lastpath[MAXPATHLEN] = "";
 	struct file_list *flist;
 	int64 start_write;
 
 	if (verbose && recurse && !am_server && f != -1) {
-		rprintf(FINFO,"building file list ... ");
+		rprintf(FINFO, RSYNC_NAME ": building file list...\n");
                 if (verbose > 1)
                         rprintf(FINFO, "\n");
 		rflush(FINFO);
 	}
 
 	start_write = stats.total_written;
