static struct file_struct *find_fuzzy(struct file_struct *file, struct file_list *dirlist_array[], uchar *fnamecmp_type_ptr)
{
	int fname_len, fname_suf_len;
	const char *fname_suf, *fname = file->basename;
	uint32 lowest_dist = 25 << 16; /* ignore a distance greater than 25 */
	int i, j;
	struct file_struct *lowest_fp = NULL;

	fname_len = strlen(fname);
	fname_suf = find_filename_suffix(fname, fname_len, &fname_suf_len);

	/* Try to find an exact size+mtime match first. */
	for (i = 0; i < fuzzy_basis; i++) {
		struct file_list *dirlist = dirlist_array[i];

		if (!dirlist)
			continue;

		for (j = 0; j < dirlist->used; j++) {
			struct file_struct *fp = dirlist->files[j];

			if (!F_IS_ACTIVE(fp))
				continue;

			if (!S_ISREG(fp->mode) || !F_LENGTH(fp) || fp->flags & FLAG_FILE_SENT)
				continue;

			if (F_LENGTH(fp) == F_LENGTH(file) && cmp_time(fp->modtime, file->modtime) == 0) {
				if (DEBUG_GTE(FUZZY, 2))
					rprintf(FINFO, "fuzzy size/modtime match for %s\n", f_name(fp, NULL));
				*fnamecmp_type_ptr = FNAMECMP_FUZZY + i;
				return fp;
			}

		}
	}

	for (i = 0; i < fuzzy_basis; i++) {
		struct file_list *dirlist = dirlist_array[i];

		if (!dirlist)
			continue;

		for (j = 0; j < dirlist->used; j++) {
			struct file_struct *fp = dirlist->files[j];
			const char *suf, *name;
			int len, suf_len;
			uint32 dist;

			if (!F_IS_ACTIVE(fp))
				continue;

			if (!S_ISREG(fp->mode) || !F_LENGTH(fp) || fp->flags & FLAG_FILE_SENT)
				continue;

			name = fp->basename;
			len = strlen(name);
			suf = find_filename_suffix(name, len, &suf_len);

			dist = fuzzy_distance(name, len, fname, fname_len);
			/* Add some extra weight to how well the suffixes match. */
			dist += fuzzy_distance(suf, suf_len, fname_suf, fname_suf_len) * 10;
			if (DEBUG_GTE(FUZZY, 2)) {
				rprintf(FINFO, "fuzzy distance for %s = %d.%05d\n",
					f_name(fp, NULL), (int)(dist>>16), (int)(dist&0xFFFF));
			}
			if (dist <= lowest_dist) {
				lowest_dist = dist;
				lowest_fp = fp;
				*fnamecmp_type_ptr = FNAMECMP_FUZZY + i;
			}
		}
	}

	return lowest_fp;
}