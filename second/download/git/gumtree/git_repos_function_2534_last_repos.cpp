struct untracked_cache *read_untracked_extension(const void *data, unsigned long sz)
{
	struct untracked_cache *uc;
	struct read_data rd;
	const unsigned char *next = data, *end = (const unsigned char *)data + sz;
	const char *ident;
	int ident_len, len;
	const char *exclude_per_dir;

	if (sz <= 1 || end[-1] != '\0')
		return NULL;
	end--;

	ident_len = decode_varint(&next);
	if (next + ident_len > end)
		return NULL;
	ident = (const char *)next;
	next += ident_len;

	if (next + ouc_size(0) > end)
		return NULL;

	uc = xcalloc(1, sizeof(*uc));
	strbuf_init(&uc->ident, ident_len);
	strbuf_add(&uc->ident, ident, ident_len);
	load_sha1_stat(&uc->ss_info_exclude,
		       next + ouc_offset(info_exclude_stat),
		       next + ouc_offset(info_exclude_sha1));
	load_sha1_stat(&uc->ss_excludes_file,
		       next + ouc_offset(excludes_file_stat),
		       next + ouc_offset(excludes_file_sha1));
	uc->dir_flags = get_be32(next + ouc_offset(dir_flags));
	exclude_per_dir = (const char *)next + ouc_offset(exclude_per_dir);
	uc->exclude_per_dir = xstrdup(exclude_per_dir);
	/* NUL after exclude_per_dir is covered by sizeof(*ouc) */
	next += ouc_size(strlen(exclude_per_dir));
	if (next >= end)
		goto done2;

	len = decode_varint(&next);
	if (next > end || len == 0)
		goto done2;

	rd.valid      = ewah_new();
	rd.check_only = ewah_new();
	rd.sha1_valid = ewah_new();
	rd.data	      = next;
	rd.end	      = end;
	rd.index      = 0;
	ALLOC_ARRAY(rd.ucd, len);

	if (read_one_dir(&uc->root, &rd) || rd.index != len)
		goto done;

	next = rd.data;
	len = ewah_read_mmap(rd.valid, next, end - next);
	if (len < 0)
		goto done;

	next += len;
	len = ewah_read_mmap(rd.check_only, next, end - next);
	if (len < 0)
		goto done;

	next += len;
	len = ewah_read_mmap(rd.sha1_valid, next, end - next);
	if (len < 0)
		goto done;

	ewah_each_bit(rd.check_only, set_check_only, &rd);
	rd.data = next + len;
	ewah_each_bit(rd.valid, read_stat, &rd);
	ewah_each_bit(rd.sha1_valid, read_sha1, &rd);
	next = rd.data;

done:
	free(rd.ucd);
	ewah_free(rd.valid);
	ewah_free(rd.check_only);
	ewah_free(rd.sha1_valid);
done2:
	if (next != end) {
		free_untracked_cache(uc);
		uc = NULL;
	}
	return uc;
}