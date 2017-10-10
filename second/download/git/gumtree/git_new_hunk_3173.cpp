{
	struct strbuf key = STRBUF_INIT;
	struct remote *remote;

	strbuf_addf(&key, "remote.%s.fetch", remotename);

	remote = remote_get(remotename);
	if (!remote_is_configured(remote))
		die(_("No such remote '%s'"), remotename);

	if (!add_mode && remove_all_fetch_refspecs(remotename, key.buf)) {
		strbuf_release(&key);
		return 1;
	}
	add_branches(remote, branches, key.buf);
