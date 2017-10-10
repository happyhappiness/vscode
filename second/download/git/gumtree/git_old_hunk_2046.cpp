	if (!(slot & EXPIRE_UNREACH))
		cb->expire_unreachable = default_reflog_expire_unreachable;
}

static int cmd_reflog_expire(int argc, const char **argv, const char *prefix)
{
	struct cmd_reflog_expire_cb cb;
	unsigned long now = time(NULL);
	int i, status, do_all;
	int explicit_expiry = 0;

	default_reflog_expire_unreachable = now - 30 * 24 * 3600;
	default_reflog_expire = now - 90 * 24 * 3600;
	git_config(reflog_expire_config, NULL);

	save_commit_buffer = 0;
	do_all = status = 0;
	memset(&cb, 0, sizeof(cb));

	cb.expire_total = default_reflog_expire;
	cb.expire_unreachable = default_reflog_expire_unreachable;

	for (i = 1; i < argc; i++) {
		const char *arg = argv[i];
		if (!strcmp(arg, "--dry-run") || !strcmp(arg, "-n"))
			cb.dry_run = 1;
		else if (starts_with(arg, "--expire=")) {
			if (parse_expiry_date(arg + 9, &cb.expire_total))
				die(_("'%s' is not a valid timestamp"), arg);
			explicit_expiry |= EXPIRE_TOTAL;
		}
		else if (starts_with(arg, "--expire-unreachable=")) {
			if (parse_expiry_date(arg + 21, &cb.expire_unreachable))
				die(_("'%s' is not a valid timestamp"), arg);
			explicit_expiry |= EXPIRE_UNREACH;
		}
		else if (!strcmp(arg, "--stale-fix"))
			cb.stalefix = 1;
		else if (!strcmp(arg, "--rewrite"))
			cb.rewrite = 1;
		else if (!strcmp(arg, "--updateref"))
			cb.updateref = 1;
		else if (!strcmp(arg, "--all"))
			do_all = 1;
		else if (!strcmp(arg, "--verbose"))
			cb.verbose = 1;
		else if (!strcmp(arg, "--")) {
			i++;
			break;
		}
		else if (arg[0] == '-')
			usage(reflog_expire_usage);
