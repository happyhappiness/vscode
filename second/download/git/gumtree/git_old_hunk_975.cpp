
	if (!sub)
		die(_("No url found for submodule path '%s' in .gitmodules"),
			displaypath);

	/*
	 * Copy url setting when it is not set yet.
	 * To look up the url in .git/config, we must not fall back to
	 * .gitmodules, so look it up directly.
	 */
	strbuf_reset(&sb);
	strbuf_addf(&sb, "submodule.%s.url", sub->name);
	if (git_config_get_string(sb.buf, &url)) {
		url = xstrdup(sub->url);

		if (!url)
			die(_("No url found for submodule path '%s' in .gitmodules"),
				displaypath);

		/* Possibly a url relative to parent */
		if (starts_with_dot_dot_slash(url) ||
		    starts_with_dot_slash(url)) {
			char *remoteurl, *relurl;
			char *remote = get_default_remote();
			struct strbuf remotesb = STRBUF_INIT;
			strbuf_addf(&remotesb, "remote.%s.url", remote);
			free(remote);

			if (git_config_get_string(remotesb.buf, &remoteurl))
				/*
				 * The repository is its own
				 * authoritative upstream
				 */
				remoteurl = xgetcwd();
			relurl = relative_url(remoteurl, url, NULL);
			strbuf_release(&remotesb);
			free(remoteurl);
			free(url);
			url = relurl;
		}
