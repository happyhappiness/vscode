static int migrate_file(struct remote *remote)
{
	struct strbuf buf = STRBUF_INIT;
	int i;

	strbuf_addf(&buf, "remote.%s.url", remote->name);
	for (i = 0; i < remote->url_nr; i++)
		if (git_config_set_multivar(buf.buf, remote->url[i], "^$", 0))
			return error(_("Could not append '%s' to '%s'"),
					remote->url[i], buf.buf);
	strbuf_reset(&buf);
	strbuf_addf(&buf, "remote.%s.push", remote->name);
	for (i = 0; i < remote->push_refspec_nr; i++)
		if (git_config_set_multivar(buf.buf, remote->push_refspec[i], "^$", 0))
			return error(_("Could not append '%s' to '%s'"),
					remote->push_refspec[i], buf.buf);
	strbuf_reset(&buf);
	strbuf_addf(&buf, "remote.%s.fetch", remote->name);
	for (i = 0; i < remote->fetch_refspec_nr; i++)
		if (git_config_set_multivar(buf.buf, remote->fetch_refspec[i], "^$", 0))
			return error(_("Could not append '%s' to '%s'"),
					remote->fetch_refspec[i], buf.buf);
	if (remote->origin == REMOTE_REMOTES)
		unlink_or_warn(git_path("remotes/%s", remote->name));
	else if (remote->origin == REMOTE_BRANCHES)
		unlink_or_warn(git_path("branches/%s", remote->name));
	return 0;
}