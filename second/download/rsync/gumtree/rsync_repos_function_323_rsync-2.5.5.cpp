static char *get_local_name(struct file_list *flist,char *name)
{
	STRUCT_STAT st;
	extern int orig_umask;

	if (verbose > 2)
		rprintf(FINFO,"get_local_name count=%d %s\n", 
			flist->count, NS(name));

	if (!name) 
		return NULL;

	if (do_stat(name,&st) == 0) {
		if (S_ISDIR(st.st_mode)) {
			if (!push_dir(name, 0)) {
				rprintf(FERROR,"push_dir %s : %s (1)\n",
					name,strerror(errno));
				exit_cleanup(RERR_FILESELECT);
			}
			return NULL;
		}
		if (flist->count > 1) {
			rprintf(FERROR,"ERROR: destination must be a directory when copying more than 1 file\n");
			exit_cleanup(RERR_FILESELECT);
		}
		return name;
	}

	if (flist->count <= 1)
		return name;

	if (do_mkdir(name,0777 & ~orig_umask) != 0) {
		rprintf(FERROR, RSYNC_NAME ": mkdir %s: %s\n",
			name, strerror(errno));
		exit_cleanup(RERR_FILEIO);
	} else {
		if (verbose > 0)
			rprintf(FINFO,"created directory %s\n",name);
	}

	if (!push_dir(name, 0)) {
		rprintf(FERROR, RSYNC_NAME ": push_dir %s: %s\n",
			name, strerror(errno));
		exit_cleanup(RERR_FILESELECT);
	}

	return NULL;
}