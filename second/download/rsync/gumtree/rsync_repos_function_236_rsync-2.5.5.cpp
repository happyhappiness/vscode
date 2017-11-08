int recv_files(int f_in,struct file_list *flist,char *local_name,int f_gen)
{  
	int fd1,fd2;
	STRUCT_STAT st;
	char *fname;
	char template[MAXPATHLEN];
	char fnametmp[MAXPATHLEN];
	char *fnamecmp;
	char fnamecmpbuf[MAXPATHLEN];
	struct map_struct *buf;
	int i;
	struct file_struct *file;
	int phase=0;
	int recv_ok;
	extern struct stats stats;		
	extern int preserve_perms;
	extern int delete_after;
	struct stats initial_stats;

	if (verbose > 2) {
		rprintf(FINFO,"recv_files(%d) starting\n",flist->count);
	}

	while (1) {      
		cleanup_disable();

		i = read_int(f_in);
		if (i == -1) {
			if (phase==0 && remote_version >= 13) {
				phase++;
				csum_length = SUM_LENGTH;
				if (verbose > 2)
					rprintf(FINFO,"recv_files phase=%d\n",phase);
				write_int(f_gen,-1);
				continue;
			}
			break;
		}

		if (i < 0 || i >= flist->count) {
			rprintf(FERROR,"Invalid file index %d in recv_files (count=%d)\n", 
				i, flist->count);
			exit_cleanup(RERR_PROTOCOL);
		}

		file = flist->files[i];
		fname = f_name(file);

		stats.num_transferred_files++;
		stats.total_transferred_size += file->length;

		if (local_name)
			fname = local_name;

		if (dry_run) {
			if (!am_server) {
				log_transfer(file, fname);
			}
			continue;
		}

		initial_stats = stats;

		if (verbose > 2)
			rprintf(FINFO,"recv_files(%s)\n",fname);

		fnamecmp = fname;

		/* open the file */  
		fd1 = do_open(fnamecmp, O_RDONLY, 0);

		if ((fd1 == -1) && (compare_dest != NULL)) {
			/* try the file at compare_dest instead */
			snprintf(fnamecmpbuf,MAXPATHLEN,"%s/%s",
						compare_dest,fname);
			fnamecmp = fnamecmpbuf;
			fd1 = do_open(fnamecmp, O_RDONLY, 0);
		}

		if (fd1 != -1 && do_fstat(fd1,&st) != 0) {
			rprintf(FERROR,"fstat %s : %s\n",fnamecmp,strerror(errno));
			receive_data(f_in,NULL,-1,NULL,file->length);
			close(fd1);
			continue;
		}

		if (fd1 != -1 && !S_ISREG(st.st_mode)) {
			rprintf(FERROR,"%s : not a regular file (recv_files)\n",fnamecmp);
			receive_data(f_in,NULL,-1,NULL,file->length);
			close(fd1);
			continue;
		}

		if (fd1 != -1 && !preserve_perms) {
			/* if the file exists already and we aren't perserving
			   presmissions then act as though the remote end sent
			   us the file permissions we already have */
			file->mode = st.st_mode;
		}

		if (fd1 != -1 && st.st_size > 0) {
			buf = map_file(fd1,st.st_size);
			if (verbose > 2)
				rprintf(FINFO,"recv mapped %s of size %.0f\n",fnamecmp,(double)st.st_size);
		} else {
			buf = NULL;
		}

		if (!get_tmpname(fnametmp,fname)) {
			if (buf) unmap_file(buf);
			if (fd1 != -1) close(fd1);
			continue;
		}

		strlcpy(template, fnametmp, sizeof(template));

		/* we initially set the perms without the
		   setuid/setgid bits to ensure that there is no race
		   condition. They are then correctly updated after
		   the lchown. Thanks to snabb@epipe.fi for pointing
		   this out.  We also set it initially without group
		   access because of a similar race condition. */
		fd2 = do_mkstemp(fnametmp, file->mode & INITACCESSPERMS);
		if (fd2 == -1) {
			rprintf(FERROR,"mkstemp %s failed: %s\n",fnametmp,strerror(errno));
			receive_data(f_in,buf,-1,NULL,file->length);
			if (buf) unmap_file(buf);
			continue;
		}

		/* in most cases parent directories will already exist
		   because their information should have been previously
		   transferred, but that may not be the case with -R */
		if (fd2 == -1 && relative_paths && errno == ENOENT && 
		    create_directory_path(fnametmp) == 0) {
			strlcpy(fnametmp, template, sizeof(fnametmp));
			fd2 = do_mkstemp(fnametmp, file->mode & INITACCESSPERMS);
		}
		if (fd2 == -1) {
			rprintf(FERROR,"cannot create %s : %s\n",fnametmp,strerror(errno));
			receive_data(f_in,buf,-1,NULL,file->length);
			if (buf) unmap_file(buf);
			if (fd1 != -1) close(fd1);
			continue;
		}
      
		cleanup_set(fnametmp, fname, file, buf, fd1, fd2);

		if (!am_server) {
			log_transfer(file, fname);
		}

		/* recv file data */
		recv_ok = receive_data(f_in,buf,fd2,fname,file->length);

		log_recv(file, &initial_stats);
		
		if (buf) unmap_file(buf);
		if (fd1 != -1) {
			close(fd1);
		}
		close(fd2);
		
		if (verbose > 2)
			rprintf(FINFO,"renaming %s to %s\n",fnametmp,fname);

		finish_transfer(fname, fnametmp, file);

		cleanup_disable();

		if (!recv_ok) {
			if (csum_length == SUM_LENGTH) {
				rprintf(FERROR,"ERROR: file corruption in %s. File changed during transfer?\n",
					fname);
			} else {
				if (verbose > 1)
					rprintf(FINFO,"redoing %s(%d)\n",fname,i);
				write_int(f_gen,i);
			}
		}
	}

	if (delete_after) {
		if (recurse && delete_mode && !local_name && flist->count>0) {
			delete_files(flist);
		}
	}

	if (preserve_hard_links)
		do_hard_links();

	/* now we need to fix any directory permissions that were 
	   modified during the transfer */
	for (i = 0; i < flist->count; i++) {
		file = flist->files[i];
		if (!file->basename || !S_ISDIR(file->mode)) continue;
		recv_generator(local_name?local_name:f_name(file),flist,i,-1);
	}

	if (verbose > 2)
		rprintf(FINFO,"recv_files finished\n");
	
	return 0;
}