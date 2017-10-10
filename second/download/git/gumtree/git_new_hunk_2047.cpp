
	/*
	 * We can trust the commits and objects reachable from refs
	 * even in older repository.  We cannot trust what's reachable
	 * from reflog if the repository was pruned with older git.
	 */
	if (cb.cmd.stalefix) {
		init_revisions(&cb.cmd.revs, prefix);
		if (flags & EXPIRE_REFLOGS_VERBOSE)
			printf("Marking reachable objects...");
		mark_reachable_objects(&cb.cmd.revs, 0, 0, NULL);
		if (flags & EXPIRE_REFLOGS_VERBOSE)
			putchar('\n');
	}

	if (do_all) {
		struct collect_reflog_cb collected;
		int i;

		memset(&collected, 0, sizeof(collected));
		for_each_reflog(collect_reflog, &collected);
		for (i = 0; i < collected.nr; i++) {
			struct collected_reflog *e = collected.e[i];
			set_reflog_expiry_param(&cb.cmd, explicit_expiry, e->reflog);
			status |= reflog_expire(e->reflog, e->sha1, flags,
						reflog_expiry_prepare,
						should_expire_reflog_ent,
						reflog_expiry_cleanup,
						&cb);
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
		set_reflog_expiry_param(&cb.cmd, explicit_expiry, ref);
		status |= reflog_expire(ref, sha1, flags,
					reflog_expiry_prepare,
					should_expire_reflog_ent,
					reflog_expiry_cleanup,
					&cb);
	}
	return status;
}

static int count_reflog_ent(unsigned char *osha1, unsigned char *nsha1,
		const char *email, unsigned long timestamp, int tz,
		const char *message, void *cb_data)
{
	struct expire_reflog_policy_cb *cb = cb_data;
	if (!cb->cmd.expire_total || timestamp < cb->cmd.expire_total)
		cb->cmd.recno++;
	return 0;
}

static int cmd_reflog_delete(int argc, const char **argv, const char *prefix)
{
	struct expire_reflog_policy_cb cb;
	int i, status = 0;
	unsigned int flags = 0;

	memset(&cb, 0, sizeof(cb));

	for (i = 1; i < argc; i++) {
		const char *arg = argv[i];
		if (!strcmp(arg, "--dry-run") || !strcmp(arg, "-n"))
			flags |= EXPIRE_REFLOGS_DRY_RUN;
		else if (!strcmp(arg, "--rewrite"))
			flags |= EXPIRE_REFLOGS_REWRITE;
		else if (!strcmp(arg, "--updateref"))
			flags |= EXPIRE_REFLOGS_UPDATE_REF;
		else if (!strcmp(arg, "--verbose"))
			flags |= EXPIRE_REFLOGS_VERBOSE;
		else if (!strcmp(arg, "--")) {
			i++;
			break;
		}
		else if (arg[0] == '-')
			usage(reflog_delete_usage);
