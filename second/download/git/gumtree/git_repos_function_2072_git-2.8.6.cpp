static void write_one_dir(struct untracked_cache_dir *untracked,
			  struct write_data *wd)
{
	struct stat_data stat_data;
	struct strbuf *out = &wd->out;
	unsigned char intbuf[16];
	unsigned int intlen, value;
	int i = wd->index++;

	/*
	 * untracked_nr should be reset whenever valid is clear, but
	 * for safety..
	 */
	if (!untracked->valid) {
		untracked->untracked_nr = 0;
		untracked->check_only = 0;
	}

	if (untracked->check_only)
		ewah_set(wd->check_only, i);
	if (untracked->valid) {
		ewah_set(wd->valid, i);
		stat_data_to_disk(&stat_data, &untracked->stat_data);
		strbuf_add(&wd->sb_stat, &stat_data, sizeof(stat_data));
	}
	if (!is_null_sha1(untracked->exclude_sha1)) {
		ewah_set(wd->sha1_valid, i);
		strbuf_add(&wd->sb_sha1, untracked->exclude_sha1, 20);
	}

	intlen = encode_varint(untracked->untracked_nr, intbuf);
	strbuf_add(out, intbuf, intlen);

	/* skip non-recurse directories */
	for (i = 0, value = 0; i < untracked->dirs_nr; i++)
		if (untracked->dirs[i]->recurse)
			value++;
	intlen = encode_varint(value, intbuf);
	strbuf_add(out, intbuf, intlen);

	strbuf_add(out, untracked->name, strlen(untracked->name) + 1);

	for (i = 0; i < untracked->untracked_nr; i++)
		strbuf_add(out, untracked->untracked[i],
			   strlen(untracked->untracked[i]) + 1);

	for (i = 0; i < untracked->dirs_nr; i++)
		if (untracked->dirs[i]->recurse)
			write_one_dir(untracked->dirs[i], wd);
}