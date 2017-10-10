
	rename.old = argv[1];
	rename.new = argv[2];
	rename.remote_branches = &remote_branches;

	oldremote = remote_get(rename.old);
	if (!remote_is_configured(oldremote, 1))
		die(_("No such remote: %s"), rename.old);

	if (!strcmp(rename.old, rename.new) && oldremote->origin != REMOTE_CONFIG)
		return migrate_file(oldremote);

	newremote = remote_get(rename.new);
	if (remote_is_configured(newremote, 1))
		die(_("remote %s already exists."), rename.new);

	strbuf_addf(&buf, "refs/heads/test:refs/remotes/%s/test", rename.new);
	if (!valid_fetch_refspec(buf.buf))
		die(_("'%s' is not a valid remote name"), rename.new);

