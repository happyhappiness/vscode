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
