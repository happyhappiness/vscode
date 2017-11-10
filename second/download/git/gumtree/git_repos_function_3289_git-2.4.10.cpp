static int reject_entry(const unsigned char *sha1, struct strbuf *base,
			const char *filename, unsigned mode,
			int stage, void *context)
{
	int ret = -1;
	if (S_ISDIR(mode)) {
		struct strbuf sb = STRBUF_INIT;
		strbuf_addbuf(&sb, base);
		strbuf_addstr(&sb, filename);
		if (!match_pathspec(context, sb.buf, sb.len, 0, NULL, 1))
			ret = READ_TREE_RECURSIVE;
		strbuf_release(&sb);
	}
	return ret;
}