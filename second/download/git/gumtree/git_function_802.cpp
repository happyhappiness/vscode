static void init_submodule(const char *path, const char *prefix, int quiet)
{
	const struct submodule *sub;
	struct strbuf sb = STRBUF_INIT;
	char *upd = NULL, *url = NULL, *displaypath;

	/* Only loads from .gitmodules, no overlay with .git/config */
	gitmodules_config();

	if (prefix && get_super_prefix())
		die("BUG: cannot have prefix and superprefix");
	else if (prefix)
		displaypath = xstrdup(relative_path(path, prefix, &sb));
	else if (get_super_prefix()) {
		strbuf_addf(&sb, "%s%s", get_super_prefix(), path);
		displaypath = strbuf_detach(&sb, NULL);
	} else
		displaypath = xstrdup(path);

	sub = submodule_from_path(null_sha1, path);

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

		if (git_config_set_gently(sb.buf, url))
			die(_("Failed to register url for submodule path '%s'"),
			    displaypath);
		if (!quiet)
			fprintf(stderr,
				_("Submodule '%s' (%s) registered for path '%s'\n"),
				sub->name, url, displaypath);
	}

	/* Copy "update" setting when it is not set yet */
	strbuf_reset(&sb);
	strbuf_addf(&sb, "submodule.%s.update", sub->name);
	if (git_config_get_string(sb.buf, &upd) &&
	    sub->update_strategy.type != SM_UPDATE_UNSPECIFIED) {
		if (sub->update_strategy.type == SM_UPDATE_COMMAND) {
			fprintf(stderr, _("warning: command update mode suggested for submodule '%s'\n"),
				sub->name);
			upd = xstrdup("none");
		} else
			upd = xstrdup(submodule_strategy_to_string(&sub->update_strategy));

		if (git_config_set_gently(sb.buf, upd))
			die(_("Failed to register update mode for submodule path '%s'"), displaypath);
	}
	strbuf_release(&sb);
	free(displaypath);
	free(url);
	free(upd);
}