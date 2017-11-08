void recv_generator(char *fname,struct file_list *flist,int i,int f_out)
{  
	int fd;
	STRUCT_STAT st;
	struct map_struct *buf;
	struct sum_struct *s;
	int statret;
	struct file_struct *file = flist->files[i];
	char *fnamecmp;
	char fnamecmpbuf[MAXPATHLEN];
	extern char *compare_dest;
	extern int list_only;
	extern int preserve_perms;
	extern int only_existing;

	if (list_only) return;

	if (verbose > 2)
		rprintf(FINFO,"recv_generator(%s,%d)\n",fname,i);

	statret = link_stat(fname,&st);

	if (only_existing && statret == -1 && errno == ENOENT) {
		/* we only want to update existing files */
		if (verbose > 1) rprintf(FINFO, "not creating new file \"%s\"\n",fname);
		return;
	}

	if (statret == 0 && 
	    !preserve_perms && 
	    (S_ISDIR(st.st_mode) == S_ISDIR(file->mode))) {
		/* if the file exists already and we aren't perserving
                   presmissions then act as though the remote end sent
                   us the file permissions we already have */
		file->mode = (file->mode & _S_IFMT) | (st.st_mode & ~_S_IFMT);
	}

	if (S_ISDIR(file->mode)) {
                /* The file to be received is a directory, so we need
                 * to prepare appropriately.  If there is already a
                 * file of that name and it is *not* a directory, then
                 * we need to delete it.  If it doesn't exist, then
                 * recursively create it. */
          
		if (dry_run) return; /* XXXX -- might cause inaccuracies?? -- mbp */
		if (statret == 0 && !S_ISDIR(st.st_mode)) {
			if (robust_unlink(fname) != 0) {
				rprintf(FERROR, RSYNC_NAME
					": recv_generator: unlink \"%s\" to make room for directory: %s\n",
                                        fname,strerror(errno));
				return;
			}
			statret = -1;
		}
		if (statret != 0 && do_mkdir(fname,file->mode) != 0 && errno != EEXIST) {
			if (!(relative_paths && errno==ENOENT && 
			      create_directory_path(fname)==0 && 
			      do_mkdir(fname,file->mode)==0)) {
				rprintf(FERROR, RSYNC_NAME ": recv_generator: mkdir \"%s\": %s (2)\n",
					fname,strerror(errno));
			}
		}
		/* f_out is set to -1 when doing final directory 
		   permission and modification time repair */
		if (set_perms(fname,file,NULL,0) && verbose && (f_out != -1)) 
			rprintf(FINFO,"%s/\n",fname);
		return;
	}

	if (preserve_links && S_ISLNK(file->mode)) {
#if SUPPORT_LINKS
		char lnk[MAXPATHLEN];
		int l;
		extern int safe_symlinks;

		if (safe_symlinks && unsafe_symlink(file->link, fname)) {
			if (verbose) {
				rprintf(FINFO,"ignoring unsafe symlink \"%s\" -> \"%s\"\n",
					fname,file->link);
			}
			return;
		}
		if (statret == 0) {
			l = readlink(fname,lnk,MAXPATHLEN-1);
			if (l > 0) {
				lnk[l] = 0;
				/* A link already pointing to the
				 * right place -- no further action
				 * required. */
				if (strcmp(lnk,file->link) == 0) {
					set_perms(fname,file,&st,1);
					return;
				}
			}  
			/* Not a symlink, so delete whatever's
			 * already there and put a new symlink
			 * in place. */			   
			delete_file(fname);
		}
		if (do_symlink(file->link,fname) != 0) {
			rprintf(FERROR,RSYNC_NAME": symlink \"%s\" -> \"%s\": %s\n",
				fname,file->link,strerror(errno));
		} else {
			set_perms(fname,file,NULL,0);
			if (verbose) {
				rprintf(FINFO,"%s -> %s\n", fname,file->link);
			}
		}
#endif
		return;
	}

#ifdef HAVE_MKNOD
	if (am_root && preserve_devices && IS_DEVICE(file->mode)) {
		if (statret != 0 || 
		    st.st_mode != file->mode ||
		    st.st_rdev != file->rdev) {	
			delete_file(fname);
			if (verbose > 2)
				rprintf(FINFO,"mknod(%s,0%o,0x%x)\n",
					fname,(int)file->mode,(int)file->rdev);
			if (do_mknod(fname,file->mode,file->rdev) != 0) {
				rprintf(FERROR,"mknod %s : %s\n",fname,strerror(errno));
			} else {
				set_perms(fname,file,NULL,0);
				if (verbose)
					rprintf(FINFO,"%s\n",fname);
			}
		} else {
			set_perms(fname,file,&st,1);
		}
		return;
	}
#endif

	if (preserve_hard_links && check_hard_link(file)) {
		if (verbose > 1)
			rprintf(FINFO, "recv_generator: \"%s\" is a hard link\n",f_name(file));
		return;
	}

	if (!S_ISREG(file->mode)) {
		rprintf(FINFO, "skipping non-regular file \"%s\"\n",fname);
		return;
	}

	fnamecmp = fname;

	if ((statret == -1) && (compare_dest != NULL)) {
		/* try the file at compare_dest instead */
		int saveerrno = errno;
		snprintf(fnamecmpbuf,MAXPATHLEN,"%s/%s",compare_dest,fname);
		statret = link_stat(fnamecmpbuf,&st);
		if (!S_ISREG(st.st_mode))
			statret = -1;
		if (statret == -1)
			errno = saveerrno;
		else
			fnamecmp = fnamecmpbuf;
	}

	if (statret == -1) {
		if (errno == ENOENT) {
			write_int(f_out,i);
			if (!dry_run) send_sums(NULL,f_out);
		} else {
			if (verbose > 1)
				rprintf(FERROR, RSYNC_NAME
					": recv_generator failed to open \"%s\": %s\n",
					fname, strerror(errno));
		}
		return;
	}

	if (!S_ISREG(st.st_mode)) {
		if (delete_file(fname) != 0) {
			return;
		}

		/* now pretend the file didn't exist */
		write_int(f_out,i);
		if (!dry_run) send_sums(NULL,f_out);    
		return;
	}

	if (opt_ignore_existing && fnamecmp == fname) { 
		if (verbose > 1)
			rprintf(FINFO,"%s exists\n",fname);
		return;
	} 

	if (update_only && cmp_modtime(st.st_mtime,file->modtime)>0 && fnamecmp == fname) {
		if (verbose > 1)
			rprintf(FINFO,"%s is newer\n",fname);
		return;
	}

	if (skip_file(fname, file, &st)) {
		if (fnamecmp == fname)
			set_perms(fname,file,&st,1);
		return;
	}

	if (dry_run) {
		write_int(f_out,i);
		return;
	}

	if (disable_deltas_p()) {
		write_int(f_out,i);
		send_sums(NULL,f_out);    
		return;
	}

	/* open the file */  
	fd = do_open(fnamecmp, O_RDONLY, 0);

	if (fd == -1) {
		rprintf(FERROR,RSYNC_NAME": failed to open \"%s\", continuing : %s\n",fnamecmp,strerror(errno));
		/* pretend the file didn't exist */
		write_int(f_out,i);
		send_sums(NULL,f_out);
		return;
	}

	if (st.st_size > 0) {
		buf = map_file(fd,st.st_size);
	} else {
		buf = NULL;
	}

	if (verbose > 3)
		rprintf(FINFO,"gen mapped %s of size %.0f\n",fnamecmp,(double)st.st_size);

	s = generate_sums(buf,st.st_size,adapt_block_size(file, block_size));

	if (verbose > 2)
		rprintf(FINFO,"sending sums for %d\n",i);

	write_int(f_out,i);
	send_sums(s,f_out);

	close(fd);
	if (buf) unmap_file(buf);

	free_sums(s);
}