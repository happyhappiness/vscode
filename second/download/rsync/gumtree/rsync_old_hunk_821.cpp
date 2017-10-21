
	if (dir)
		free(dir);

	return ret;

oom:
	out_of_memory("do_cmd");
	return 0; /* not reached */
}


static char *get_local_name(struct file_list *flist,char *name)
{
	STRUCT_STAT st;
	int e;

	if (verbose > 2)
		rprintf(FINFO,"get_local_name count=%d %s\n",
			flist->count, NS(name));

	if (!name)
		return NULL;

	if (do_stat(name,&st) == 0) {
		if (S_ISDIR(st.st_mode)) {
			if (!push_dir(name)) {
				rsyserr(FERROR, errno, "push_dir#1 %s failed",
					full_fname(name));
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

	if (flist->count <= 1 && ((e = strlen(name)) <= 1 || name[e-1] != '/'))
		return name;

	if (do_mkdir(name,0777 & ~orig_umask) != 0) {
		rsyserr(FERROR, errno, "mkdir %s failed", full_fname(name));
		exit_cleanup(RERR_FILEIO);
	}
	if (verbose > 0)
		rprintf(FINFO, "created directory %s\n", safe_fname(name));

	if (dry_run) {
		dry_run++;
		return NULL;
	}

	if (!push_dir(name)) {
		rsyserr(FERROR, errno, "push_dir#2 %s failed",
			full_fname(name));
		exit_cleanup(RERR_FILESELECT);
	}

	return NULL;
}


/* This is only called by the sender. */
static void read_final_goodbye(int f_in, int f_out)
{
