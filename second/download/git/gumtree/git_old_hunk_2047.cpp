
	/*
	 * We can trust the commits and objects reachable from refs
	 * even in older repository.  We cannot trust what's reachable
	 * from reflog if the repository was pruned with older git.
	 */
	if (cb.stalefix) {
		init_revisions(&cb.revs, prefix);
		if (cb.verbose)
			printf("Marking reachable objects...");
		mark_reachable_objects(&cb.revs, 0, 0, NULL);
		if (cb.verbose)
			putchar('\n');
	}

	if (do_all) {
		struct collect_reflog_cb collected;
		int i;

		memset(&collected, 0, sizeof(collected));
		for_each_reflog(collect_reflog, &collected);
		for (i = 0; i < collected.nr; i++) {
			struct collected_reflog *e = collected.e[i];
			set_reflog_expiry_param(&cb, explicit_expiry, e->reflog);
			status |= expire_reflog(e->reflog, e->sha1, 0, &cb);
			free(e);
		}
		free(collected.e);
	}

	for (; i < argc; i++) {
		char *ref;
		unsigned char sha1[20];
		if (!dwim_log(argv[i], strlen(argv[i]), sha1, &ref)) {
			status |= error("%s points nowhere!", argv[i]);
			continue;
		}
		set_reflog_expiry_param(&cb, explicit_expiry, ref);
		status |= expire_reflog(ref, sha1, 0, &cb);
	}
	return status;
}

static int count_reflog_ent(unsigned char *osha1, unsigned char *nsha1,
		const char *email, unsigned long timestamp, int tz,
		const char *message, void *cb_data)
{
	struct cmd_reflog_expire_cb *cb = cb_data;
	if (!cb->expire_total || timestamp < cb->expire_total)
		cb->recno++;
	return 0;
}

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
