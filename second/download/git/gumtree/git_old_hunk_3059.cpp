	case AUTOREBASE_ALWAYS:
		return 1;
	}
	return 0;
}

void install_branch_config(int flag, const char *local, const char *origin, const char *remote)
{
	const char *shortname = NULL;
	struct strbuf key = STRBUF_INIT;
	int rebasing = should_setup_rebase(origin);

	if (skip_prefix(remote, "refs/heads/", &shortname)
	    && !strcmp(local, shortname)
	    && !origin) {
		warning(_("Not setting branch %s as its own upstream."),
			local);
		return;
	}

	strbuf_addf(&key, "branch.%s.remote", local);
	git_config_set(key.buf, origin ? origin : ".");

	strbuf_reset(&key);
	strbuf_addf(&key, "branch.%s.merge", local);
	git_config_set(key.buf, remote);

	if (rebasing) {
		strbuf_reset(&key);
		strbuf_addf(&key, "branch.%s.rebase", local);
		git_config_set(key.buf, "true");
	}
	strbuf_release(&key);

	if (flag & BRANCH_CONFIG_VERBOSE) {
		if (shortname) {
			if (origin)
