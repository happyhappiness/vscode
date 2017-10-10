	refspec = parse_fetch_refspec(1, &fetch_pattern);

	strbuf_reset(&value);

	remote = remote_get(option_origin);
	transport = transport_get(remote, remote->url[0]);
	path = get_repo_path(remote->url[0], &is_bundle);
	is_local = option_local != 0 && path && !is_bundle;
	if (is_local) {
		if (option_depth)
			warning(_("--depth is ignored in local clones; use file:// instead."));
		if (!access(mkpath("%s/shallow", path), F_OK)) {
			if (option_local > 0)
				warning(_("source repository is shallow, ignoring --local"));
			is_local = 0;
		}
	}
	if (option_local > 0 && !is_local)
		warning(_("--local is ignored"));
	transport->cloning = 1;

	if (!transport->get_refs_list || (!is_local && !transport->fetch))
		die(_("Don't know how to clone %s"), transport->url);

	transport_set_option(transport, TRANS_OPT_KEEP, "yes");
