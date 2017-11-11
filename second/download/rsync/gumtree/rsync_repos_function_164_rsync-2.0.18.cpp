int recv_files(int f_in,struct file_list *flist,char *local_name,int f_gen)
{  
	int fd1,fd2;
	STRUCT_STAT st;
	char *fname;
	char fnametmp[MAXPATHLEN];
	struct map_struct *buf;
	int i;
	struct file_struct *file;
	int phase=0;
	int recv_ok;
	
	if (verbose > 2) {
		rprintf(FINFO,"recv_files(%d) starting\n",flist->count);
	}

	if (recurse && delete_mode && !local_name && flist->count>0) {
		delete_files(flist);
	}

	while (1) {      
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
			exit_cleanup(1);
		}

		file = flist->files[i];
		fname = f_name(file);

		stats.num_transferred_files++;
		stats.total_transferred_size += file->length;

		if (local_name)
			fname = local_name;

		if (dry_run) {
			if (!am_server && verbose)
				printf("%s\n",fname);
			continue;
		}

		if (verbose > 2)
			rprintf(FINFO,"recv_files(%s)\n",fname);

		/* open the file */  
		fd1 = open(fname,O_RDONLY);

		if (fd1 != -1 && do_fstat(fd1,&st) != 0) {
			rprintf(FERROR,"fstat %s : %s\n",fname,strerror(errno));
			receive_data(f_in,NULL,-1,NULL);
			close(fd1);
			continue;
		}

		if (fd1 != -1 && !S_ISREG(st.st_mode)) {
			rprintf(FERROR,"%s : not a regular file (recv_files)\n",fname);
			receive_data(f_in,NULL,-1,NULL);
			close(fd1);
			continue;
		}

		if (fd1 != -1 && st.st_size > 0) {
			buf = map_file(fd1,st.st_size);
			if (verbose > 2)
				rprintf(FINFO,"recv mapped %s of size %d\n",fname,(int)st.st_size);
		} else {
			buf = NULL;
		}

		if (!get_tmpname(fnametmp,fname)) {
			if (buf) unmap_file(buf);
			close(fd1);
			continue;
		}

		if (NULL == do_mktemp(fnametmp)) {
			rprintf(FERROR,"mktemp %s failed\n",fnametmp);
			receive_data(f_in,buf,-1,NULL);
			if (buf) unmap_file(buf);
			close(fd1);
			continue;
		}

		/* we initially set the perms without the
		   setuid/setgid bits to ensure that there is no race
		   condition. They are then correctly updated after
		   the lchown. Thanks to snabb@epipe.fi for pointing
		   this out */
		fd2 = do_open(fnametmp,O_WRONLY|O_CREAT|O_EXCL,
			      file->mode & ACCESSPERMS);

		if (fd2 == -1 && relative_paths && errno == ENOENT && 
		    create_directory_path(fnametmp) == 0) {
			fd2 = do_open(fnametmp,O_WRONLY|O_CREAT|O_EXCL,
				      file->mode & ACCESSPERMS);
		}
		if (fd2 == -1) {
			rprintf(FERROR,"open %s : %s\n",fnametmp,strerror(errno));
			receive_data(f_in,buf,-1,NULL);
			if (buf) unmap_file(buf);
			close(fd1);
			continue;
		}
      
		cleanup_fname = fnametmp;

		if (!am_server && verbose)
			printf("%s\n",fname);
		
		/* recv file data */
		recv_ok = receive_data(f_in,buf,fd2,fname);
		
		if (buf) unmap_file(buf);
		if (fd1 != -1) {
			close(fd1);
		}
		close(fd2);
		
		if (verbose > 2)
			rprintf(FINFO,"renaming %s to %s\n",fnametmp,fname);
		
		if (make_backups) {
			char fnamebak[MAXPATHLEN];
			if (strlen(fname) + strlen(backup_suffix) > (MAXPATHLEN-1)) {
				rprintf(FERROR,"backup filename too long\n");
				continue;
			}
			slprintf(fnamebak,sizeof(fnamebak)-1,"%s%s",fname,backup_suffix);
			if (do_rename(fname,fnamebak) != 0 && errno != ENOENT) {
				rprintf(FERROR,"rename %s %s : %s\n",fname,fnamebak,strerror(errno));
				continue;
			}
		}

		/* move tmp file over real file */
		if (do_rename(fnametmp,fname) != 0) {
			if (errno == EXDEV) {
				/* rename failed on cross-filesystem link.  
				   Copy the file instead. */
				if (copy_file(fnametmp,fname, file->mode)) {
					rprintf(FERROR,"copy %s -> %s : %s\n",
						fnametmp,fname,strerror(errno));
				} else {
					set_perms(fname,file,NULL,0);
				}
				do_unlink(fnametmp);
			} else {
				rprintf(FERROR,"rename %s -> %s : %s\n",
					fnametmp,fname,strerror(errno));
				do_unlink(fnametmp);
			}
		} else {
			set_perms(fname,file,NULL,0);
		}

		cleanup_fname = NULL;

		
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

	if (preserve_hard_links)
		do_hard_links(flist);

	/* now we need to fix any directory permissions that were 
	   modified during the transfer */
	for (i = 0; i < flist->count; i++) {
		file = flist->files[i];
		if (!file->basename || !S_ISDIR(file->mode)) continue;
		recv_generator(f_name(file),flist,i,-1);
	}

	if (verbose > 2)
		rprintf(FINFO,"recv_files finished\n");
	
	return 0;
}