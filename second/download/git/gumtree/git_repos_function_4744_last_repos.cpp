static void write_tree_entry(struct strbuf *buf, unsigned int mode,
		const char *path, unsigned int path_len, const
		unsigned char *sha1)
{
	strbuf_addf(buf, "%o %.*s%c", mode, path_len, path, '\0');
	strbuf_add(buf, sha1, GIT_SHA1_RAWSZ);
}