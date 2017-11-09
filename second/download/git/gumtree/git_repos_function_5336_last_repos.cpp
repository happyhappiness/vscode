static void create_object_directory(void)
{
	struct strbuf path = STRBUF_INIT;
	size_t baselen;

	strbuf_addstr(&path, get_object_directory());
	baselen = path.len;

	safe_create_dir(path.buf, 1);

	strbuf_setlen(&path, baselen);
	strbuf_addstr(&path, "/pack");
	safe_create_dir(path.buf, 1);

	strbuf_setlen(&path, baselen);
	strbuf_addstr(&path, "/info");
	safe_create_dir(path.buf, 1);

	strbuf_release(&path);
}