static void check_embedded_repo(const char *path)
{
	struct strbuf name = STRBUF_INIT;

	if (!warn_on_embedded_repo)
		return;
	if (!ends_with(path, "/"))
		return;

	/* Drop trailing slash for aesthetics */
	strbuf_addstr(&name, path);
	strbuf_strip_suffix(&name, "/");

	warning(_("adding embedded git repository: %s"), name.buf);
	if (advice_add_embedded_repo) {
		advise(embedded_advice, name.buf, name.buf);
		/* there may be multiple entries; advise only once */
		advice_add_embedded_repo = 0;
	}

	strbuf_release(&name);
}