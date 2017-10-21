 			if ((p = strstr(fbuf, "/./")) != NULL) {
 				*p = '\0';
 				if (p == fbuf)
 					dir = "/";
 				else
 					dir = fbuf;
-				len -= p - fbuf + 3;
 				fn = p + 3;
+				while (*fn == '/')
+					fn++;
+				if (!*fn)
+					*--fn = '\0'; /* ensure room for '.' */
 			} else
 				fn = fbuf;
-			/* Get rid of trailing "/" and "/.". */
-			while (len) {
-				if (fn[len - 1] == '/') {
-					is_dot_dir = 1;
-					if (!--len && !dir) {
-						len++;
-						break;
-					}
-				}
-				else if (len >= 2 && fn[len - 1] == '.'
-						  && fn[len - 2] == '/') {
-					is_dot_dir = 1;
-					if (!(len -= 2) && !dir) {
-						len++;
-						break;
-					}
-				} else
-					break;
+			len = clean_fname(fn, CFN_KEEP_LEADING_DOT_DIR
+					    | CFN_KEEP_TRAILING_SLASH
+					    | CFN_DROP_TRAILING_DOT_DIR);
+			if (len == 1) {
+				if (fn[0] == '/') {
+					fn = "/.";
+					len = 2;
+					name_type = DOT_NAME;
+				} else if (fn[0] == '.')
+					name_type = DOT_NAME;
+			} else if (fn[len-1] == '/') {
+				fn[--len] = '\0';
+				if (len == 1 && *fn == '.')
+					name_type = DOT_NAME;
+				else
+					name_type = SLASH_ENDING_NAME;
 			}
-			if (len == 1 && fn[0] == '/')
-				fn[len++] = '.';
-			fn[len] = '\0';
 			/* Reject a ".." dir in the active part of the path. */
 			for (p = fn; (p = strstr(p, "..")) != NULL; p += 2) {
 				if ((p[2] == '/' || p[2] == '\0')
 				 && (p == fn || p[-1] == '/')) {
 					rprintf(FERROR,
 					    "found \"..\" dir in relative path: %s\n",
-					    fbuf);
+					    fn);
 					exit_cleanup(RERR_SYNTAX);
 				}
 			}
 		}
 
 		if (!*fn) {
 			len = 1;
 			fn = ".";
+			name_type = DOT_NAME;
 		}
 
-		if (dir && *dir) {
-			static char *lastdir;
-			static int lastdir_len;
-
-			strlcpy(olddir, curr_dir, sizeof olddir);
-
-			if (!push_dir(dir, 0)) {
-				io_error |= IOERR_GENERAL;
-				rsyserr(FERROR, errno, "push_dir %s failed",
-					full_fname(dir));
+		dirlen = dir ? strlen(dir) : 0;
+		if (dirlen != lastdir_len || memcmp(lastdir, dir, dirlen) != 0) {
+			if (!push_pathname(dir ? strdup(dir) : NULL, dirlen))
 				continue;
-			}
-
-			if (lastdir && strcmp(lastdir, dir) == 0) {
-				flist_dir = lastdir;
-				flist_dir_len = lastdir_len;
-			} else {
-				flist_dir = lastdir = strdup(dir);
-				flist_dir_len = lastdir_len = strlen(dir);
-			}
-		}
+			lastdir = pathname;
+			lastdir_len = pathname_len;
+		} else if (!push_pathname(lastdir, lastdir_len))
+			continue;
 
 		if (fn != fbuf)
 			memmove(fbuf, fn, len + 1);
 
-		if (implied_dirs && (p=strrchr(fbuf,'/')) && p != fbuf) {
+		if (link_stat(fbuf, &st, copy_dirlinks || name_type != NORMAL_NAME) != 0) {
+			io_error |= IOERR_GENERAL;
+			rsyserr(FERROR_XFER, errno, "link_stat %s failed",
+				full_fname(fbuf));
+			continue;
+		}
+
+		if (S_ISDIR(st.st_mode) && !xfer_dirs) {
+			rprintf(FINFO, "skipping directory %s\n", fbuf);
+			continue;
+		}
+
+		if (inc_recurse && relative_paths && *fbuf) {
+			if ((p = strchr(fbuf+1, '/')) != NULL) {
+				if (p - fbuf == 1 && *fbuf == '.') {
+					if ((fn = strchr(p+1, '/')) != NULL)
+						p = fn;
+				} else
+					fn = p;
+				send_implied_dirs(f, flist, fbuf, fbuf, p, flags, name_type);
+				if (fn == p)
+					continue;
+			}
+		} else if (implied_dirs && (p=strrchr(fbuf,'/')) && p != fbuf) {
 			/* Send the implied directories at the start of the
 			 * source spec, so we get their permissions right. */
 			char *lp = lastpath, *slash = fbuf;
 			*p = '\0';
 			/* Skip any initial directories in our path that we
 			 * have in common with lastpath. */
 			for (fn = fbuf; *fn && *lp == *fn; lp++, fn++) {
 				if (*fn == '/')
 					slash = fn;
 			}
 			*p = '/';
-			if (fn != p || (*lp && *lp != '/')) {
-				int save_copy_links = copy_links;
-				int save_xfer_dirs = xfer_dirs;
-				copy_links |= copy_unsafe_links;
-				xfer_dirs = 1;
-				while ((slash = strchr(slash+1, '/')) != 0) {
-					*slash = '\0';
-					send_file_name(f, flist, fbuf, NULL, 0);
-					*slash = '/';
-				}
-				copy_links = save_copy_links;
-				xfer_dirs = save_xfer_dirs;
-				*p = '\0';
-				strlcpy(lastpath, fbuf, sizeof lastpath);
-				*p = '/';
-			}
+			if (fn != p || (*lp && *lp != '/'))
+				send_implied_dirs(f, flist, fbuf, slash, p, flags, 0);
 		}
 
 		if (one_file_system)
 			filesystem_dev = st.st_dev;
 
-		if (recurse || (xfer_dirs && is_dot_dir)) {
+		if (recurse || (xfer_dirs && name_type != NORMAL_NAME)) {
 			struct file_struct *file;
-			file = send_file_name(f, flist, fbuf, &st, FLAG_TOP_DIR);
-			if (file)
-				send_if_directory(f, flist, file, fbuf, len);
+			int top_flags = FLAG_TOP_DIR | FLAG_CONTENT_DIR | flags;
+			file = send_file_name(f, flist, fbuf, &st,
+					      top_flags, ALL_FILTERS);
+			if (inc_recurse) {
+				if (name_type == DOT_NAME && file) {
+					if (send_dir_depth < 0) {
+						send_dir_depth = 0;
+						change_local_filter_dir(fbuf, len, send_dir_depth);
+					}
+					send_directory(f, flist, fbuf, len, flags);
+				}
+			} else if (file)
+				send_if_directory(f, flist, file, fbuf, len, flags);
 		} else
-			send_file_name(f, flist, fbuf, &st, 0);
-
-		if (olddir[0]) {
-			flist_dir = NULL;
-			flist_dir_len = 0;
-			if (!pop_dir(olddir)) {
-				rsyserr(FERROR, errno, "pop_dir %s failed",
-					full_fname(olddir));
-				exit_cleanup(RERR_FILESELECT);
-			}
-		}
+			send_file_name(f, flist, fbuf, &st, flags, ALL_FILTERS);
 	}
 
 	gettimeofday(&end_tv, NULL);
 	stats.flist_buildtime = (int64)(end_tv.tv_sec - start_tv.tv_sec) * 1000
 			      + (end_tv.tv_usec - start_tv.tv_usec) / 1000;
 	if (stats.flist_buildtime == 0)
 		stats.flist_buildtime = 1;
 	start_tv = end_tv;
 
-	send_file_entry(NULL, f);
+	write_byte(f, 0); /* Indicate end of file list */
+
+#ifdef SUPPORT_HARD_LINKS
+	if (preserve_hard_links && protocol_version >= 30 && !inc_recurse)
+		idev_destroy();
+#endif
 
 	if (show_filelist_p())
 		finish_filelist_progress(flist);
 
 	gettimeofday(&end_tv, NULL);
 	stats.flist_xfertime = (int64)(end_tv.tv_sec - start_tv.tv_sec) * 1000
 			     + (end_tv.tv_usec - start_tv.tv_usec) / 1000;
 
-	if (flist->hlink_pool) {
-		pool_destroy(flist->hlink_pool);
-		flist->hlink_pool = NULL;
-	}
+	/* When converting names, both sides keep an unsorted file-list array
+	 * because the names will differ on the sending and receiving sides
+	 * (both sides will use the unsorted index number for each item). */
 
 	/* Sort the list without removing any duplicates.  This allows the
-	 * receiving side to ask for any name they like, which gives us the
-	 * flexibility to change the way we unduplicate names in the future
-	 * without causing a compatibility problem with older versions. */
-	clean_flist(flist, 0, 0);
+	 * receiving side to ask for whatever name it kept.  For incremental
+	 * recursion mode, the sender marks duplicate dirs so that it can
+	 * send them together in a single file-list. */
+	if (need_unsorted_flist) {
+		if (!(flist->sorted = new_array(struct file_struct *, flist->used)))
+			out_of_memory("send_file_list");
+		memcpy(flist->sorted, flist->files,
+		       flist->used * sizeof (struct file_struct*));
+	} else
+		flist->sorted = flist->files;
+	flist_sort_and_clean(flist, 0);
+	file_total += flist->used;
 
-	send_uid_list(f);
+	if (numeric_ids <= 0 && !inc_recurse)
+		send_id_list(f);
 
 	/* send the io_error flag */
-	write_int(f, lp_ignore_errors(module_id) ? 0 : io_error);
+	if (protocol_version < 30)
+		write_int(f, ignore_errors ? 0 : io_error);
+	else if (io_error && !ignore_errors)
+		send_msg_int(MSG_IO_ERROR, io_error);
+
+	if (disable_buffering)
+		io_end_buffering_out();
 
-	io_end_buffering();
 	stats.flist_size = stats.total_written - start_write;
-	stats.num_files = flist->count;
+	stats.num_files = flist->used;
 
 	if (verbose > 3)
 		output_flist(flist);
 
 	if (verbose > 2)
 		rprintf(FINFO, "send_file_list done\n");
 
+	if (inc_recurse) {
+		send_dir_depth = 1;
+		add_dirs_to_tree(-1, flist, dir_count);
+		if (!file_total || strcmp(flist->sorted[0]->basename, ".") != 0) 
+			flist->parent_ndx = -1;
+		flist_done_allocating(flist);
+		if (send_dir_ndx < 0) {
+			write_ndx(f, NDX_FLIST_EOF);
+			flist_eof = 1;
+		}
+		else if (file_total == 1) {
+			/* If we're creating incremental file-lists and there
+			 * was just 1 item in the first file-list, send 1 more
+			 * file-list to check if this is a 1-file xfer. */
+			send_extra_file_list(f, 1);
+		}
+	}
+
 	return flist;
 }
 
 struct file_list *recv_file_list(int f)
 {
 	struct file_list *flist;
-	unsigned short flags;
+	int dstart, flags;
 	int64 start_read;
 
-	rprintf(FLOG, "receiving file list\n");
+	if (!first_flist)
+		rprintf(FLOG, "receiving file list\n");
 	if (show_filelist_p())
 		start_filelist_progress("receiving file list");
+	else if (inc_recurse && verbose && !am_server && !first_flist)
+		rprintf(FCLIENT, "receiving incremental file list\n");
 
 	start_read = stats.total_read;
 
-	flist = flist_new(WITH_HLINK, "recv_file_list");
+#ifdef SUPPORT_HARD_LINKS
+	if (preserve_hard_links && !first_flist)
+		init_hard_links();
+#endif
 
-	flist->count = 0;
-	flist->malloced = 1000;
-	flist->files = new_array(struct file_struct *, flist->malloced);
-	if (!flist->files)
-		goto oom;
+	flist = flist_new(0, "recv_file_list");
+
+	if (inc_recurse) {
+		if (flist->ndx_start == 1)
+			dir_flist = flist_new(FLIST_TEMP, "recv_file_list");
+		dstart = dir_flist->used;
+	} else {
+		dir_flist = flist;
+		dstart = 0;
+	}
 
 	while ((flags = read_byte(f)) != 0) {
 		struct file_struct *file;
 
-		flist_expand(flist);
+		flist_expand(flist, 1);
 
 		if (protocol_version >= 28 && (flags & XMIT_EXTENDED_FLAGS))
 			flags |= read_byte(f) << 8;
-		file = receive_file_entry(flist, flags, f);
+		file = recv_file_entry(flist, flags, f);
 
-		if (S_ISREG(file->mode) || S_ISLNK(file->mode))
-			stats.total_size += file->length;
+		if (inc_recurse && S_ISDIR(file->mode)) {
+			flist_expand(dir_flist, 1);
+			dir_flist->files[dir_flist->used++] = file;
+		}
 
-		flist->files[flist->count++] = file;
+		flist->files[flist->used++] = file;
 
-		maybe_emit_filelist_progress(flist->count);
+		maybe_emit_filelist_progress(flist->used);
 
 		if (verbose > 2) {
 			rprintf(FINFO, "recv_file_name(%s)\n",
 				f_name(file, NULL));
 		}
 	}
-	receive_file_entry(NULL, 0, 0); /* Signal that we're done. */
+	file_total += flist->used;
 
 	if (verbose > 2)
-		rprintf(FINFO, "received %d names\n", flist->count);
+		rprintf(FINFO, "received %d names\n", flist->used);
 
 	if (show_filelist_p())
 		finish_filelist_progress(flist);
 
-	clean_flist(flist, relative_paths, 1);
+	if (need_unsorted_flist) {
+		/* Create an extra array of index pointers that we can sort for
+		 * the generator's use (for wading through the files in sorted
+		 * order and for calling flist_find()).  We keep the "files"
+		 * list unsorted for our exchange of index numbers with the
+		 * other side (since their names may not sort the same). */
+		if (!(flist->sorted = new_array(struct file_struct *, flist->used)))
+			out_of_memory("recv_file_list");
+		memcpy(flist->sorted, flist->files,
+		       flist->used * sizeof (struct file_struct*));
+		if (inc_recurse && dir_flist->used > dstart) {
+			static int dir_flist_malloced = 0;
+			if (dir_flist_malloced < dir_flist->malloced) {
+				dir_flist->sorted = realloc_array(dir_flist->sorted,
+							struct file_struct *,
+							dir_flist->malloced);
+				dir_flist_malloced = dir_flist->malloced;
+			}
+			memcpy(dir_flist->sorted + dstart, dir_flist->files + dstart,
+			       (dir_flist->used - dstart) * sizeof (struct file_struct*));
+			fsort(dir_flist->sorted + dstart, dir_flist->used - dstart);
+		}
+	} else {
+		flist->sorted = flist->files;
+		if (inc_recurse && dir_flist->used > dstart) {
+			dir_flist->sorted = dir_flist->files;
+			fsort(dir_flist->sorted + dstart, dir_flist->used - dstart);
+		}
+	}
+
+	if (inc_recurse)
+		flist_done_allocating(flist);
+	else if (f >= 0)
+		recv_id_list(f, flist);
 
-	if (f >= 0) {
-		recv_uid_list(f, flist);
+	flist_sort_and_clean(flist, relative_paths);
 
+	if (protocol_version < 30) {
 		/* Recv the io_error flag */
-		if (lp_ignore_errors(module_id) || ignore_errors)
+		if (ignore_errors)
 			read_int(f);
 		else
 			io_error |= read_int(f);
+	} else if (inc_recurse && flist->ndx_start == 1) {
+		if (!file_total || strcmp(flist->sorted[0]->basename, ".") != 0) 
+			flist->parent_ndx = -1;
 	}
 
 	if (verbose > 3)
 		output_flist(flist);
 
-	if (list_only) {
-		int i;
-		for (i = 0; i < flist->count; i++)
-			list_file_entry(flist->files[i]);
-	}
-
 	if (verbose > 2)
 		rprintf(FINFO, "recv_file_list done\n");
 
-	stats.flist_size = stats.total_read - start_read;
-	stats.num_files = flist->count;
+	stats.flist_size += stats.total_read - start_read;
+	stats.num_files += flist->used;
 
 	return flist;
-
-  oom:
-	out_of_memory("recv_file_list");
-	return NULL;		/* not reached */
 }
 
-static int file_compare(struct file_struct **file1, struct file_struct **file2)
+/* This is only used once by the receiver if the very first file-list
+ * has exactly one item in it. */
+void recv_additional_file_list(int f)
 {
-	return f_name_cmp(*file1, *file2);
+	struct file_list *flist;
+	int ndx = read_ndx(f);
+	if (ndx == NDX_FLIST_EOF) {
+		flist_eof = 1;
+		change_local_filter_dir(NULL, 0, 0);
+	} else {
+		ndx = NDX_FLIST_OFFSET - ndx;
+		if (ndx < 0 || ndx >= dir_flist->used) {
+			ndx = NDX_FLIST_OFFSET - ndx;
+			rprintf(FERROR,
+				"[%s] Invalid dir index: %d (%d - %d)\n",
+				who_am_i(), ndx, NDX_FLIST_OFFSET,
+				NDX_FLIST_OFFSET - dir_flist->used + 1);
+			exit_cleanup(RERR_PROTOCOL);
+		}
+		if (verbose > 3) {
+			rprintf(FINFO, "[%s] receiving flist for dir %d\n",
+				who_am_i(), ndx);
+		}
+		flist = recv_file_list(f);
+		flist->parent_ndx = ndx;
+	}
 }
 
 /* Search for an identically-named item in the file list.  Note that the
  * items must agree in their directory-ness, or no match is returned. */
 int flist_find(struct file_list *flist, struct file_struct *f)
 {
 	int low = flist->low, high = flist->high;
 	int diff, mid, mid_up;
 
 	while (low <= high) {
 		mid = (low + high) / 2;
-		if (flist->files[mid]->basename)
+		if (F_IS_ACTIVE(flist->sorted[mid]))
 			mid_up = mid;
 		else {
 			/* Scan for the next non-empty entry using the cached
 			 * distance values.  If the value isn't fully up-to-
 			 * date, update it. */
-			mid_up = mid + flist->files[mid]->dir.depth;
-			if (!flist->files[mid_up]->basename) {
+			mid_up = mid + F_DEPTH(flist->sorted[mid]);
+			if (!F_IS_ACTIVE(flist->sorted[mid_up])) {
 				do {
-				    mid_up += flist->files[mid_up]->dir.depth;
-				} while (!flist->files[mid_up]->basename);
-				flist->files[mid]->dir.depth = mid_up - mid;
+				    mid_up += F_DEPTH(flist->sorted[mid_up]);
+				} while (!F_IS_ACTIVE(flist->sorted[mid_up]));
+				F_DEPTH(flist->sorted[mid]) = mid_up - mid;
 			}
 			if (mid_up > high) {
 				/* If there's nothing left above us, set high to
 				 * a non-empty entry below us and continue. */
-				high = mid - flist->files[mid]->length;
-				if (!flist->files[high]->basename) {
+				high = mid - (int)flist->sorted[mid]->len32;
+				if (!F_IS_ACTIVE(flist->sorted[high])) {
 					do {
-					    high -= flist->files[high]->length;
-					} while (!flist->files[high]->basename);
-					flist->files[mid]->length = mid - high;
+					    high -= (int)flist->sorted[high]->len32;
+					} while (!F_IS_ACTIVE(flist->sorted[high]));
+					flist->sorted[mid]->len32 = mid - high;
 				}
 				continue;
 			}
 		}
-		diff = f_name_cmp(flist->files[mid_up], f);
+		diff = f_name_cmp(flist->sorted[mid_up], f);
 		if (diff == 0) {
 			if (protocol_version < 29
-			    && S_ISDIR(flist->files[mid_up]->mode)
+			    && S_ISDIR(flist->sorted[mid_up]->mode)
 			    != S_ISDIR(f->mode))
 				return -1;
 			return mid_up;
 		}
 		if (diff < 0)
 			low = mid_up + 1;
