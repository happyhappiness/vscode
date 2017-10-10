
	git_config_get_int("gc.aggressivewindow", &aggressive_window);
	git_config_get_int("gc.aggressivedepth", &aggressive_depth);
	git_config_get_int("gc.auto", &gc_auto_threshold);
	git_config_get_int("gc.autopacklimit", &gc_auto_pack_limit);
	git_config_get_bool("gc.autodetach", &detach_auto);
	git_config_get_expiry("gc.pruneexpire", &prune_expire);
	git_config_get_expiry("gc.worktreepruneexpire", &prune_worktrees_expire);
	git_config_get_expiry("gc.logexpiry", &gc_log_expire);

	git_config(git_default_config, NULL);
}

static int too_many_loose_objects(void)
{
	/*
	 * Quickly check if a "gc" is needed, by estimating how
	 * many loose objects there are.  Because SHA-1 is evenly
	 * distributed, we can check only one and get a reasonable
	 * estimate.
	 */
	DIR *dir;
	struct dirent *ent;
	int auto_threshold;
	int num_loose = 0;
	int needed = 0;

	if (gc_auto_threshold <= 0)
		return 0;

	dir = opendir(git_path("objects/17"));
	if (!dir)
		return 0;

	auto_threshold = (gc_auto_threshold + 255) / 256;
	while ((ent = readdir(dir)) != NULL) {
		if (strspn(ent->d_name, "0123456789abcdef") != 38 ||
