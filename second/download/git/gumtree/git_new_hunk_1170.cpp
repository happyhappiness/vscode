	if (get_oid("HEAD", &orig_head))
		oidclr(&orig_head);

	if (!opt_rebase && opt_autostash != -1)
		die(_("--[no-]autostash option is only valid with --rebase."));

	autostash = config_autostash;
	if (opt_rebase) {
		if (opt_autostash != -1)
			autostash = opt_autostash;

		if (is_null_oid(&orig_head) && !is_cache_unborn())
			die(_("Updating an unborn branch with changes added to the index."));

