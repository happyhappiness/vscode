static void read_remotes_file(struct remote *remote)
{
	struct strbuf buf = STRBUF_INIT;
	FILE *f = fopen_or_warn(git_path("remotes/%s", remote->name), "r");

	if (!f)
		return;
	remote->configured_in_repo = 1;
	remote->origin = REMOTE_REMOTES;
	while (strbuf_getline(&buf, f) != EOF) {
		const char *v;

		strbuf_rtrim(&buf);

		if (skip_prefix(buf.buf, "URL:", &v))
			add_url_alias(remote, xstrdup(skip_spaces(v)));
		else if (skip_prefix(buf.buf, "Push:", &v))
			add_push_refspec(remote, xstrdup(skip_spaces(v)));
		else if (skip_prefix(buf.buf, "Pull:", &v))
			add_fetch_refspec(remote, xstrdup(skip_spaces(v)));
	}
	strbuf_release(&buf);
	fclose(f);
}