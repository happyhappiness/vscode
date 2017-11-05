static void exec_man_konqueror(const char *path, const char *page)
{
	const char *display = getenv("DISPLAY");
	if (display && *display) {
		struct strbuf man_page = STRBUF_INIT;
		const char *filename = "kfmclient";

		/* It's simpler to launch konqueror using kfmclient. */
		if (path) {
			size_t len;
			if (strip_suffix(path, "/konqueror", &len))
				path = xstrfmt("%.*s/kfmclient", (int)len, path);
			filename = basename((char *)path);
		} else
			path = "kfmclient";
		strbuf_addf(&man_page, "man:%s(1)", page);
		execlp(path, filename, "newTab", man_page.buf, (char *)NULL);
		warning(_("failed to exec '%s': %s"), path, strerror(errno));
	}
}