static int cmd_reflog_delete(int argc, const char **argv, const char *prefix)
{
	struct cmd_reflog_expire_cb cb;
	int i, status = 0;

	memset(&cb, 0, sizeof(cb));

	for (i = 1; i < argc; i++) {
		const char *arg = argv[i];
		if (!strcmp(arg, "--dry-run") || !strcmp(arg, "-n"))
			cb.dry_run = 1;
		else if (!strcmp(arg, "--rewrite"))
			cb.rewrite = 1;
		else if (!strcmp(arg, "--updateref"))
			cb.updateref = 1;
		else if (!strcmp(arg, "--verbose"))
			cb.verbose = 1;
		else if (!strcmp(arg, "--")) {
			i++;
			break;
		}
		else if (arg[0] == '-')
			usage(reflog_delete_usage);
		else
			break;
	}

	if (argc - i < 1)
		return error("Nothing to delete?");

	for ( ; i < argc; i++) {
		const char *spec = strstr(argv[i], "@{");
		unsigned char sha1[20];
		char *ep, *ref;
		int recno;

		if (!spec) {
			status |= error("Not a reflog: %s", argv[i]);
			continue;
		}

		if (!dwim_log(argv[i], spec - argv[i], sha1, &ref)) {
			status |= error("no reflog for '%s'", argv[i]);
			continue;
		}

		recno = strtoul(spec + 2, &ep, 10);
		if (*ep == '}') {
			cb.recno = -recno;
			for_each_reflog_ent(ref, count_reflog_ent, &cb);
		} else {
			cb.expire_total = approxidate(spec + 2);
			for_each_reflog_ent(ref, count_reflog_ent, &cb);
			cb.expire_total = 0;
		}

		status |= expire_reflog(ref, sha1, 0, &cb);
		free(ref);
	}
	return status;
}