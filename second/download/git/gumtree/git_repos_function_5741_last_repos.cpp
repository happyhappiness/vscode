static int git_fetch_config(const char *k, const char *v, void *cb)
{
	if (!strcmp(k, "fetch.prune")) {
		fetch_prune_config = git_config_bool(k, v);
		return 0;
	}

	if (!strcmp(k, "submodule.recurse")) {
		int r = git_config_bool(k, v) ?
			RECURSE_SUBMODULES_ON : RECURSE_SUBMODULES_OFF;
		recurse_submodules = r;
	}

	return git_default_config(k, v, cb);
}