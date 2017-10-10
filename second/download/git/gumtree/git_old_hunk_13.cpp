	if (states.stale.nr) {
		printf_ln(_("Pruning %s"), remote);
		printf_ln(_("URL: %s"),
		       states.remote->url_nr
		       ? states.remote->url[0]
		       : _("(no URL)"));
	}

	for (i = 0; i < states.stale.nr; i++) {
		const char *refname = states.stale.items[i].util;

		if (!dry_run)
			result |= delete_ref(refname, NULL, 0);

		if (dry_run)
			printf_ln(_(" * [would prune] %s"),
			       abbrev_ref(refname, "refs/remotes/"));
		else
			printf_ln(_(" * [pruned] %s"),
			       abbrev_ref(refname, "refs/remotes/"));
		warn_dangling_symref(stdout, dangling_msg, refname);
	}

	free_remote_ref_states(&states);
	return result;
}

static int prune(int argc, const char **argv)
{
