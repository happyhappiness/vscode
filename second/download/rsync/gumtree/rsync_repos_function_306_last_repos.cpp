int unchanged_file(char *fn, struct file_struct *file, STRUCT_STAT *st)
{
	if (st->st_size != F_LENGTH(file))
		return 0;

	/* if always checksum is set then we use the checksum instead
	   of the file time to determine whether to sync */
	if (always_checksum > 0 && S_ISREG(st->st_mode)) {
		char sum[MAX_DIGEST_LEN];
		file_checksum(fn, st, sum);
		return memcmp(sum, F_SUM(file), checksum_len) == 0;
	}

	if (size_only > 0)
		return 1;

	if (ignore_times)
		return 0;

	return cmp_time(st->st_mtime, file->modtime) == 0;
}