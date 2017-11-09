static int migrate_one(struct strbuf *src, struct strbuf *dst)
{
	struct stat st;

	if (stat(src->buf, &st) < 0)
		return -1;
	if (S_ISDIR(st.st_mode)) {
		if (!mkdir(dst->buf, 0777)) {
			if (adjust_shared_perm(dst->buf))
				return -1;
		} else if (errno != EEXIST)
			return -1;
		return migrate_paths(src, dst);
	}
	return finalize_object_file(src->buf, dst->buf);
}