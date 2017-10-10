
	return git_default_config(var, value, cb);
}

static void show_ref(const char *path, const unsigned char *sha1)
{
	if (ref_is_hidden(path))
		return;

	if (sent_capabilities) {
		packet_write(1, "%s %s\n", sha1_to_hex(sha1), path);
	} else {
		struct strbuf cap = STRBUF_INIT;

		strbuf_addstr(&cap,
