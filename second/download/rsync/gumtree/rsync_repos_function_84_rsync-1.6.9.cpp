static int skip_file(char *fname,
		     struct file_struct *file, struct stat *st)
{
	if (st->st_size != file->length) {
		return 0;
	}
	
	/* if always checksum is set then we use the checksum instead 
	   of the file time to determine whether to sync */
	if (always_checksum && S_ISREG(st->st_mode)) {
		char sum[MD4_SUM_LENGTH];
		file_checksum(fname,sum,st->st_size);
		return (memcmp(sum,file->sum,csum_length) == 0);
	}

	if (ignore_times) {
		return 0;
	}

	return (st->st_mtime == file->modtime);
}