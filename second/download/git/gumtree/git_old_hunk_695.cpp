		oldurl = argv[3];

	if (delete_mode)
		oldurl = newurl;

	remote = remote_get(remotename);
	if (!remote_is_configured(remote))
		die(_("No such remote '%s'"), remotename);

	if (push_mode) {
		strbuf_addf(&name_buf, "remote.%s.pushurl", remotename);
		urlset = remote->pushurl;
		urlset_nr = remote->pushurl_nr;
