void install_branch_config(int flag, const char *local, const char *origin, const char *remote)
{
	const char *shortname = skip_prefix(remote, "refs/heads/");
	struct strbuf key = STRBUF_INIT;
	int rebasing = should_setup_rebase(origin);

	if (shortname
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
				printf_ln(rebasing ?
					  _("Branch %s set up to track remote branch %s from %s by rebasing.") :
					  _("Branch %s set up to track remote branch %s from %s."),
					  local, shortname, origin);
			else
				printf_ln(rebasing ?
					  _("Branch %s set up to track local branch %s by rebasing.") :
					  _("Branch %s set up to track local branch %s."),
					  local, shortname);
		} else {
			if (origin)
				printf_ln(rebasing ?
					  _("Branch %s set up to track remote ref %s by rebasing.") :
					  _("Branch %s set up to track remote ref %s."),
					  local, remote);
			else
				printf_ln(rebasing ?
					  _("Branch %s set up to track local ref %s by rebasing.") :
					  _("Branch %s set up to track local ref %s."),
					  local, remote);
		}
	}
}