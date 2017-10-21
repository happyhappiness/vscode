 	flist = flist_new();
 
 	if (f != -1) {
 		io_start_buffering(f);
 	}
 
-	for (i=0;i<argc;i++) {
+	for (i = 0; i < argc; i++) {
 		char *fname = topsrcname;
 
-		strlcpy(fname,argv[i],MAXPATHLEN);
+		strlcpy(fname, argv[i], MAXPATHLEN);
 
 		l = strlen(fname);
-		if (l != 1 && fname[l-1] == '/') {
+		if (l != 1 && fname[l - 1] == '/') {
 			if ((l == 2) && (fname[0] == '.')) {
 				/*  Turn ./ into just . rather than ./.
-				    This was put in to avoid a problem with
-				      rsync -aR --delete from ./
-				    The send_file_name() below of ./ was
-				    mysteriously preventing deletes */
+				   This was put in to avoid a problem with
+				   rsync -aR --delete from ./
+				   The send_file_name() below of ./ was
+				   mysteriously preventing deletes */
 				fname[1] = 0;
 			} else {
-				strlcat(fname,".",MAXPATHLEN);
+				strlcat(fname, ".", MAXPATHLEN);
 			}
 		}
 
-		if (link_stat(fname,&st) != 0) {
+		if (link_stat(fname, &st) != 0) {
 			if (f != -1) {
-				io_error=1;
-				rprintf(FERROR,"link_stat %s : %s\n",fname,strerror(errno));
+				io_error = 1;
+				rprintf(FERROR, "link_stat %s : %s\n",
+					fname, strerror(errno));
 			}
 			continue;
 		}
 
 		if (S_ISDIR(st.st_mode) && !recurse) {
-			rprintf(FINFO,"skipping directory %s\n",fname);
+			rprintf(FINFO, "skipping directory %s\n", fname);
 			continue;
 		}
 
 		dir = NULL;
 		olddir = NULL;
 
 		if (!relative_paths) {
-			p = strrchr(fname,'/');
+			p = strrchr(fname, '/');
 			if (p) {
 				*p = 0;
-				if (p == fname) 
+				if (p == fname)
 					dir = "/";
 				else
-					dir = fname;      
-				fname = p+1;      
+					dir = fname;
+				fname = p + 1;
 			}
-		} else if (f != -1 && (p=strrchr(fname,'/'))) {
+		} else if (f != -1 && (p = strrchr(fname, '/'))) {
 			/* this ensures we send the intermediate directories,
 			   thus getting their permissions right */
 			*p = 0;
-			if (strcmp(lastpath,fname)) {
+			if (strcmp(lastpath, fname)) {
 				strlcpy(lastpath, fname, sizeof(lastpath));
 				*p = '/';
-				for (p=fname+1; (p=strchr(p,'/')); p++) {
+				for (p = fname + 1; (p = strchr(p, '/'));
+				     p++) {
 					int copy_links_saved = copy_links;
 					int recurse_saved = recurse;
 					*p = 0;
 					copy_links = copy_unsafe_links;
 					/* set recurse to 1 to prevent make_file
 					   from ignoring directory, but still
 					   turn off the recursive parameter to
 					   send_file_name */
 					recurse = 1;
-					send_file_name(f, flist, fname, 0, 0);
+					send_file_name(f, flist, fname, 0,
+						       0);
 					copy_links = copy_links_saved;
 					recurse = recurse_saved;
 					*p = '/';
 				}
 			} else {
 				*p = '/';
 			}
 		}
-		
+
 		if (!*fname)
 			fname = ".";
-		
+
 		if (dir && *dir) {
 			olddir = push_dir(dir, 1);
 
 			if (!olddir) {
-				io_error=1;
-				rprintf(FERROR,"push_dir %s : %s\n",
-					dir,strerror(errno));
+				io_error = 1;
+				rprintf(FERROR, "push_dir %s : %s\n",
+					dir, strerror(errno));
 				continue;
 			}
 
 			flist_dir = dir;
 		}
-		
+
 		if (one_file_system)
 			set_filesystem(fname);
 
-		send_file_name(f,flist,fname,recurse,FLAG_DELETE);
+		send_file_name(f, flist, fname, recurse, FLAG_DELETE);
 
 		if (olddir != NULL) {
 			flist_dir = NULL;
 			if (pop_dir(olddir) != 0) {
-				rprintf(FERROR,"pop_dir %s : %s\n",
-					dir,strerror(errno));
+				rprintf(FERROR, "pop_dir %s : %s\n",
+					dir, strerror(errno));
 				exit_cleanup(RERR_FILESELECT);
 			}
 		}
 	}
 
 	topsrcname[0] = '\0';
 
 	if (f != -1) {
-		send_file_entry(NULL,f,0);
+		send_file_entry(NULL, f, 0);
 	}
 
-	if (verbose && recurse && !am_server && f != -1)
-		rprintf(FINFO,"done\n");
-	
+	finish_build_progress(flist);
+
 	clean_flist(flist, 0);
-	
+
 	/* now send the uid/gid list. This was introduced in protocol
            version 15 */
 	if (f != -1 && remote_version >= 15) {
 		send_uid_list(f);
 	}
 
 	/* if protocol version is >= 17 then send the io_error flag */
 	if (f != -1 && remote_version >= 17) {
 		extern int module_id;
-		write_int(f, lp_ignore_errors(module_id)? 0 : io_error);
+		write_int(f, lp_ignore_errors(module_id) ? 0 : io_error);
 	}
 
 	if (f != -1) {
-		io_end_buffering(f);
+		io_end_buffering();
 		stats.flist_size = stats.total_written - start_write;
 		stats.num_files = flist->count;
-		if (write_batch) /*  dw  */
-		    write_batch_flist_info(flist->count, flist->files);
+		if (write_batch)	/*  dw  */
+			write_batch_flist_info(flist->count, flist->files);
 	}
 
 	if (verbose > 2)
-		rprintf(FINFO,"send_file_list done\n");
+		rprintf(FINFO, "send_file_list done\n");
 
 	return flist;
 }
 
 
 struct file_list *recv_file_list(int f)
 {
-  struct file_list *flist;
-  unsigned char flags;
-  int64 start_read;
-  extern int list_only;
-
-  if (verbose && recurse && !am_server) {
-    rprintf(FINFO,"receiving file list ... ");
-    rflush(FINFO);
-  }
+	struct file_list *flist;
+	unsigned char flags;
+	int64 start_read;
+	extern int list_only;
 
-  start_read = stats.total_read;
+	if (verbose && recurse && !am_server) {
+		rprintf(FINFO, "receiving file list ... ");
+		rflush(FINFO);
+	}
 
-  flist = (struct file_list *)malloc(sizeof(flist[0]));
-  if (!flist)
-    goto oom;
+	start_read = stats.total_read;
 
-  flist->count=0;
-  flist->malloced=1000;
-  flist->files = (struct file_struct **)malloc(sizeof(flist->files[0])*
-					       flist->malloced);
-  if (!flist->files)
-    goto oom;
+	flist = (struct file_list *) malloc(sizeof(flist[0]));
+	if (!flist)
+		goto oom;
 
+	flist->count = 0;
+	flist->malloced = 1000;
+	flist->files =
+	    (struct file_struct **) malloc(sizeof(flist->files[0]) *
+					   flist->malloced);
+	if (!flist->files)
+		goto oom;
 
-  for (flags=read_byte(f); flags; flags=read_byte(f)) {
-    int i = flist->count;
 
-    if (i >= flist->malloced) {
-	  if (flist->malloced < 1000)
-		  flist->malloced += 1000;
-	  else
-		  flist->malloced *= 2;
-	  flist->files =(struct file_struct **)realloc(flist->files,
-						       sizeof(flist->files[0])*
-						       flist->malloced);
-	  if (!flist->files)
-		  goto oom;
-    }
+	for (flags = read_byte(f); flags; flags = read_byte(f)) {
+		int i = flist->count;
+		
+		flist_expand(flist);
 
-    receive_file_entry(&flist->files[i],flags,f);
+		receive_file_entry(&flist->files[i], flags, f);
 
-    if (S_ISREG(flist->files[i]->mode))
-	    stats.total_size += flist->files[i]->length;
+		if (S_ISREG(flist->files[i]->mode))
+			stats.total_size += flist->files[i]->length;
 
-    flist->count++;
+		flist->count++;
 
-    if (verbose > 2)
-      rprintf(FINFO,"recv_file_name(%s)\n",f_name(flist->files[i]));
-  }
+		if (verbose > 2)
+			rprintf(FINFO, "recv_file_name(%s)\n",
+				f_name(flist->files[i]));
+	}
 
 
-  if (verbose > 2)
-    rprintf(FINFO,"received %d names\n",flist->count);
+	if (verbose > 2)
+		rprintf(FINFO, "received %d names\n", flist->count);
 
-  clean_flist(flist, relative_paths);
+	clean_flist(flist, relative_paths);
 
-  if (verbose && recurse && !am_server) {
-    rprintf(FINFO,"done\n");
-  }
+	if (verbose && recurse && !am_server) {
+		rprintf(FINFO, "done\n");
+	}
 
-  /* now recv the uid/gid list. This was introduced in protocol version 15 */
-  if (f != -1 && remote_version >= 15) {
-	  recv_uid_list(f, flist);
-  }
+	/* now recv the uid/gid list. This was introduced in protocol version 15 */
+	if (f != -1 && remote_version >= 15) {
+		recv_uid_list(f, flist);
+	}
 
-  /* if protocol version is >= 17 then recv the io_error flag */
-  if (f != -1 && remote_version >= 17  && !read_batch) {  /* dw-added readbatch */
-	  extern int module_id;
-	  extern int ignore_errors;
-	  if (lp_ignore_errors(module_id) || ignore_errors) {
-		  read_int(f);
-	  } else {
-		  io_error |= read_int(f);
-	  }
-  }
+	/* if protocol version is >= 17 then recv the io_error flag */
+	if (f != -1 && remote_version >= 17 && !read_batch) {	/* dw-added readbatch */
+		extern int module_id;
+		extern int ignore_errors;
+		if (lp_ignore_errors(module_id) || ignore_errors) {
+			read_int(f);
+		} else {
+			io_error |= read_int(f);
+		}
+	}
 
-  if (list_only) {
-	  int i;
-	  for (i=0;i<flist->count;i++) {
-		  list_file_entry(flist->files[i]);
-	  }
-  }
+	if (list_only) {
+		int i;
+		for (i = 0; i < flist->count; i++) {
+			list_file_entry(flist->files[i]);
+		}
+	}
 
 
-  if (verbose > 2)
-    rprintf(FINFO,"recv_file_list done\n");
+	if (verbose > 2)
+		rprintf(FINFO, "recv_file_list done\n");
 
-  stats.flist_size = stats.total_read - start_read;
-  stats.num_files = flist->count;
+	stats.flist_size = stats.total_read - start_read;
+	stats.num_files = flist->count;
 
-  return flist;
+	return flist;
 
-oom:
-    out_of_memory("recv_file_list");
-    return NULL; /* not reached */
+      oom:
+	out_of_memory("recv_file_list");
+	return NULL;		/* not reached */
 }
 
 
-int file_compare(struct file_struct **f1,struct file_struct **f2)
+/*
+ * XXX: This is currently the hottest function while building the file
+ * list, because building f_name()s every time is expensive.
+ **/
+int file_compare(struct file_struct **f1, struct file_struct **f2)
 {
-	if (!(*f1)->basename && !(*f2)->basename) return 0;
-	if (!(*f1)->basename) return -1;
-	if (!(*f2)->basename) return 1;
+	if (!(*f1)->basename && !(*f2)->basename)
+		return 0;
+	if (!(*f1)->basename)
+		return -1;
+	if (!(*f2)->basename)
+		return 1;
 	if ((*f1)->dirname == (*f2)->dirname)
 		return u_strcmp((*f1)->basename, (*f2)->basename);
-	return u_strcmp(f_name(*f1),f_name(*f2));
+	return u_strcmp(f_name(*f1), f_name(*f2));
 }
 
 
-int flist_find(struct file_list *flist,struct file_struct *f)
+int flist_find(struct file_list *flist, struct file_struct *f)
 {
-	int low=0,high=flist->count-1;
+	int low = 0, high = flist->count - 1;
 
-	if (flist->count <= 0) return -1;
+	if (flist->count <= 0)
+		return -1;
 
 	while (low != high) {
-		int mid = (low+high)/2;
-		int ret = file_compare(&flist->files[flist_up(flist, mid)],&f);
-		if (ret == 0) return flist_up(flist, mid);
+		int mid = (low + high) / 2;
+		int ret =
+		    file_compare(&flist->files[flist_up(flist, mid)], &f);
+		if (ret == 0)
+			return flist_up(flist, mid);
 		if (ret > 0) {
-			high=mid;
+			high = mid;
 		} else {
-			low=mid+1;
+			low = mid + 1;
 		}
 	}
 
-	if (file_compare(&flist->files[flist_up(flist,low)],&f) == 0)
-		return flist_up(flist,low);
+	if (file_compare(&flist->files[flist_up(flist, low)], &f) == 0)
+		return flist_up(flist, low);
 	return -1;
 }
 
 
 /*
  * free up one file
  */
 void free_file(struct file_struct *file)
 {
-	if (!file) return;
-	if (file->basename) free(file->basename);
-	if (file->link) free(file->link);
-	if (file->sum) free(file->sum);
+	if (!file)
+		return;
+	if (file->basename)
+		free(file->basename);
+	if (file->link)
+		free(file->link);
+	if (file->sum)
+		free(file->sum);
 	*file = null_file;
 }
 
 
 /*
  * allocate a new file list
  */
 struct file_list *flist_new()
 {
 	struct file_list *flist;
 
-	flist = (struct file_list *)malloc(sizeof(flist[0]));
-	if (!flist) out_of_memory("send_file_list");
+	flist = (struct file_list *) malloc(sizeof(flist[0]));
+	if (!flist)
+		out_of_memory("send_file_list");
+
+	flist->count = 0;
+	flist->malloced = 0;
+	flist->files = NULL;
 
-	flist->count=0;
-	flist->malloced = 1000;
-	flist->files = (struct file_struct **)malloc(sizeof(flist->files[0])*
-						     flist->malloced);
-	if (!flist->files) out_of_memory("send_file_list");
 #if ARENA_SIZE > 0
 	flist->string_area = string_area_new(0);
 #else
 	flist->string_area = NULL;
 #endif
 	return flist;
