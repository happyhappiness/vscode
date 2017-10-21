static struct file_struct *make_file(char *fname)
{
	struct file_struct *file;
	struct stat st;
	char sum[SUM_LENGTH];
	char *p;
	char cleaned_name[MAXPATHLEN];

	strncpy(cleaned_name, fname, MAXPATHLEN-1);
	cleaned_name[MAXPATHLEN-1] = 0;
	clean_fname(cleaned_name);
	fname = cleaned_name;

	bzero(sum,SUM_LENGTH);

	if (link_stat(fname,&st) != 0) {
		io_error = 1;
		fprintf(FERROR,"%s: %s\n",
			fname,strerror(errno));
		return NULL;
	}

	if (S_ISDIR(st.st_mode) && !recurse) {
		fprintf(FINFO,"skipping directory %s\n",fname);
		return NULL;
	}
	
	if (one_file_system && st.st_dev != filesystem_dev) {
		if (skip_filesystem(fname, &st))
			return NULL;
	}
	
	if (!match_file_name(fname,&st))
		return NULL;
	
	if (verbose > 2)
		fprintf(FINFO,"make_file(%s)\n",fname);
	
	file = (struct file_struct *)malloc(sizeof(*file));
	if (!file) out_of_memory("make_file");
	bzero((char *)file,sizeof(*file));

	if ((p = strrchr(fname,'/'))) {
		static char *lastdir;
		*p = 0;
		if (lastdir && strcmp(fname, lastdir)==0) {
			file->dirname = lastdir;
		} else {
			file->dirname = strdup(fname);
			lastdir = file->dirname;
		}
		file->basename = strdup(p+1);
		*p = '/';
	} else {
		file->dirname = NULL;
		file->basename = strdup(fname);
	}

	file->modtime = st.st_mtime;
	file->length = st.st_size;
	file->mode = st.st_mode;
	file->uid = st.st_uid;
	file->gid = st.st_gid;
	file->dev = st.st_dev;
	file->inode = st.st_ino;
#ifdef HAVE_ST_RDEV
	file->rdev = st.st_rdev;
#endif

#if SUPPORT_LINKS
	if (S_ISLNK(st.st_mode)) {
		int l;
		char lnk[MAXPATHLEN];
		if ((l=readlink(fname,lnk,MAXPATHLEN-1)) == -1) {
			io_error=1;
			fprintf(FERROR,"readlink %s : %s\n",
				fname,strerror(errno));
			return NULL;
		}
		lnk[l] = 0;
		file->link = strdup(lnk);
	}
#endif

	if (always_checksum && S_ISREG(st.st_mode)) {
		file->sum = (char *)malloc(MD4_SUM_LENGTH);
		if (!file->sum) out_of_memory("md4 sum");
		file_checksum(fname,file->sum,st.st_size);
	}       

	if (flist_dir) {
		static char *lastdir;
		if (lastdir && strcmp(lastdir, flist_dir)==0) {
			file->basedir = lastdir;
		} else {
			file->basedir = strdup(flist_dir);
			lastdir = file->basedir;
		}
	} else {
		file->basedir = NULL;
	}

	if (!S_ISDIR(st.st_mode))
		total_size += st.st_size;

	return file;
}