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
		file->link = STRDUP(ap, linkbuf);
	}
#endif

	if (always_checksum) {
		file->sum = (char *)MALLOC(ap, MD4_SUM_LENGTH);
		if (!file->sum) out_of_memory("md4 sum");
		/* drat. we have to provide a null checksum for non-regular
		   files in order to be compatible with earlier versions
		   of rsync */
		if (S_ISREG(st.st_mode)) {
			file_checksum(fname,file->sum,st.st_size);
		} else {
			memset(file->sum, 0, MD4_SUM_LENGTH);
		}
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
