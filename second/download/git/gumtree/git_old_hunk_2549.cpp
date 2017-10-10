}

static int migrate_file(struct remote *remote)
{
	struct strbuf buf = STRBUF_INIT;
	int i;
	const char *path = NULL;

	strbuf_addf(&buf, "remote.%s.url", remote->name);
	for (i = 0; i < remote->url_nr; i++)
		if (git_config_set_multivar(buf.buf, remote->url[i], "^$", 0))
			return error(_("Could not append '%s' to '%s'"),
					remote->url[i], buf.buf);
