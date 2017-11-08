static void prune_object_dir(const char *path)
{
	struct strbuf buf = STRBUF_INIT;
	size_t baselen;
	int i;

	strbuf_addstr(&buf, path);
	strbuf_addch(&buf, '/');
	baselen = buf.len;

	for (i = 0; i < 256; i++) {
		strbuf_addf(&buf, "%02x", i);
		prune_dir(i, &buf);
		strbuf_setlen(&buf, baselen);
	}
}