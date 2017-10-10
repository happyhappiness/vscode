
	strbuf_reset(&value);

	remote = remote_get(option_origin);
	transport = transport_get(remote, remote->url[0]);
	transport_set_verbosity(transport, option_verbosity, option_progress);
	transport->family = family;

	path = get_repo_path(remote->url[0], &is_bundle);
	is_local = option_local != 0 && path && !is_bundle;
	if (is_local) {
		if (option_depth)
			warning(_("--depth is ignored in local clones; use file:// instead."));
