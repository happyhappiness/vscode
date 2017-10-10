			 */
			die("--reflog is incompatible with --all, --remotes, "
			    "--independent or --merge-base");
	}

	/* If nothing is specified, show all branches by default */
	if (ac + all_heads + all_remotes == 0)
		all_heads = 1;

	if (reflog) {
		unsigned char sha1[20];
		char *ref;
		int base = 0;
		unsigned int flags = 0;

		if (ac == 0) {
			static const char *fake_av[2];

			fake_av[0] = resolve_refdup("HEAD",
						    RESOLVE_REF_READING,
						    sha1, NULL);
			fake_av[1] = NULL;
			av = fake_av;
			ac = 1;
		}
		if (ac != 1)
			die("--reflog option needs one branch name");

		if (MAX_REVS < reflog)
			die("Only %d entries can be shown at one time.",
			    MAX_REVS);
		if (!dwim_ref(*av, strlen(*av), sha1, &ref))
			die("No such ref %s", *av);

		/* Has the base been specified? */
		if (reflog_base) {
			char *ep;
			base = strtoul(reflog_base, &ep, 10);
			if (*ep) {
				/* Ah, that is a date spec... */
				unsigned long at;
				at = approxidate(reflog_base);
				read_ref_at(ref, flags, at, -1, sha1, NULL,
					    NULL, NULL, &base);
			}
		}

		for (i = 0; i < reflog; i++) {
			char *logmsg;
			char *nth_desc;
			const char *msg;
			unsigned long timestamp;
			int tz;

			if (read_ref_at(ref, flags, 0, base+i, sha1, &logmsg,
					&timestamp, &tz, NULL)) {
				reflog = i;
				break;
			}
			msg = strchr(logmsg, '\t');
			if (!msg)
