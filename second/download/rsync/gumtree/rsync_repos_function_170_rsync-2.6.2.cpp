static int skip_file(char *fname, struct file_struct *file, STRUCT_STAT *st)
{
	if (st->st_size != file->length) {
		return 0;
	}
	if (link_dest) {
		if (preserve_perms
		    && (st->st_mode & CHMOD_BITS) != (file->mode & CHMOD_BITS))
			return 0;

		if (am_root && preserve_uid && st->st_uid != file->uid)
			return 0;

		if (preserve_gid && file->gid != GID_NONE
		    && st->st_gid != file->gid)
			return 0;
	}

	/* if always checksum is set then we use the checksum instead
	   of the file time to determine whether to sync */
	if (always_checksum && S_ISREG(st->st_mode)) {
		char sum[MD4_SUM_LENGTH];
		char fnamecmpdest[MAXPATHLEN];

		if (compare_dest != NULL) {
			if (access(fname, 0) != 0) {
				pathjoin(fnamecmpdest, sizeof fnamecmpdest,
					 compare_dest, fname);
				fname = fnamecmpdest;
			}
		}
		file_checksum(fname,sum,st->st_size);
		return memcmp(sum, file->u.sum, protocol_version < 21 ? 2
							: MD4_SUM_LENGTH) == 0;
	}

	if (size_only) {
		return 1;
	}

	if (ignore_times) {
		return 0;
	}

	return (cmp_modtime(st->st_mtime,file->modtime) == 0);
}