static void gc_config(void)
{
	const char *value;

	if (!git_config_get_value("gc.packrefs", &value)) {
		if (value && !strcmp(value, "notbare"))
			pack_refs = -1;
		else
			pack_refs = git_config_bool("gc.packrefs", value);
	}

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