
	if (!sub)
		die(_("No url found for submodule path '%s' in .gitmodules"),
			displaypath);

	/*
	 * NEEDSWORK: In a multi-working-tree world, this needs to be
	 * set in the per-worktree config.
	 *
	 * Set active flag for the submodule being initialized
	 */
	if (!is_submodule_initialized(path)) {
		strbuf_reset(&sb);
		strbuf_addf(&sb, "submodule.%s.active", sub->name);
		git_config_set_gently(sb.buf, "true");
	}

	/*
	 * Copy url setting when it is not set yet.
	 * To look up the url in .git/config, we must not fall back to
	 * .gitmodules, so look it up directly.
	 */
	strbuf_reset(&sb);
	strbuf_addf(&sb, "submodule.%s.url", sub->name);
	if (git_config_get_string(sb.buf, &url)) {
		if (!sub->url)
			die(_("No url found for submodule path '%s' in .gitmodules"),
				displaypath);

		url = xstrdup(sub->url);

		/* Possibly a url relative to parent */
		if (starts_with_dot_dot_slash(url) ||
		    starts_with_dot_slash(url)) {
			char *remoteurl, *relurl;
			char *remote = get_default_remote();
			struct strbuf remotesb = STRBUF_INIT;
			strbuf_addf(&remotesb, "remote.%s.url", remote);
			free(remote);

			if (git_config_get_string(remotesb.buf, &remoteurl)) {
				warning(_("could not lookup configuration '%s'. Assuming this repository is its own authoritative upstream."), remotesb.buf);
				remoteurl = xgetcwd();
			}
			relurl = relative_url(remoteurl, url, NULL);
			strbuf_release(&remotesb);
			free(remoteurl);
			free(url);
			url = relurl;
		}
