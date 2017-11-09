static struct rerere_dir *find_rerere_dir(const char *hex)
{
	unsigned char sha1[20];
	struct rerere_dir *rr_dir;
	int pos;

	if (get_sha1_hex(hex, sha1))
		return NULL; /* BUG */
	pos = sha1_pos(sha1, rerere_dir, rerere_dir_nr, rerere_dir_sha1);
	if (pos < 0) {
		rr_dir = xmalloc(sizeof(*rr_dir));
		hashcpy(rr_dir->sha1, sha1);
		rr_dir->status = NULL;
		rr_dir->status_nr = 0;
		rr_dir->status_alloc = 0;
		pos = -1 - pos;

		/* Make sure the array is big enough ... */
		ALLOC_GROW(rerere_dir, rerere_dir_nr + 1, rerere_dir_alloc);
		/* ... and add it in. */
		rerere_dir_nr++;
		memmove(rerere_dir + pos + 1, rerere_dir + pos,
			(rerere_dir_nr - pos - 1) * sizeof(*rerere_dir));
		rerere_dir[pos] = rr_dir;
		scan_rerere_dir(rr_dir);
	}
	return rerere_dir[pos];
}