static int migrate_paths(struct strbuf *src, struct strbuf *dst)
{
	size_t src_len = src->len, dst_len = dst->len;
	struct string_list paths = STRING_LIST_INIT_DUP;
	int i;
	int ret = 0;

	if (read_dir_paths(&paths, src->buf) < 0)
		return -1;
	paths.cmp = pack_copy_cmp;
	string_list_sort(&paths);

	for (i = 0; i < paths.nr; i++) {
		const char *name = paths.items[i].string;

		strbuf_addf(src, "/%s", name);
		strbuf_addf(dst, "/%s", name);

		ret |= migrate_one(src, dst);

		strbuf_setlen(src, src_len);
		strbuf_setlen(dst, dst_len);
	}

	string_list_clear(&paths, 0);
	return ret;
}