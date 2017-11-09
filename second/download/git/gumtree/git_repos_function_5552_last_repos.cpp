int cmd_show_branch(int ac, const char **av, const char *prefix)
{
	struct commit *rev[MAX_REVS], *commit;
	char *reflog_msg[MAX_REVS];
	struct commit_list *list = NULL, *seen = NULL;
	unsigned int rev_mask[MAX_REVS];
	int num_rev, i, extra = 0;
	int all_heads = 0, all_remotes = 0;
	int all_mask, all_revs;
	enum rev_sort_order sort_order = REV_SORT_IN_GRAPH_ORDER;
	char *head;
	struct object_id head_oid;
	int merge_base = 0;
	int independent = 0;
	int no_name = 0;
	int sha1_name = 0;
	int shown_merge_point = 0;
	int with_current_branch = 0;
	int head_at = -1;
	int topics = 0;
	int dense = 1;
	const char *reflog_base = NULL;
	struct option builtin_show_branch_options[] = {
		OPT_BOOL('a', "all", &all_heads,
			 N_("show remote-tracking and local branches")),
		OPT_BOOL('r', "remotes", &all_remotes,
			 N_("show remote-tracking branches")),
		OPT__COLOR(&showbranch_use_color,
			    N_("color '*!+-' corresponding to the branch")),
		{ OPTION_INTEGER, 0, "more", &extra, N_("n"),
			    N_("show <n> more commits after the common ancestor"),
			    PARSE_OPT_OPTARG, NULL, (intptr_t)1 },
		OPT_SET_INT(0, "list", &extra, N_("synonym to more=-1"), -1),
		OPT_BOOL(0, "no-name", &no_name, N_("suppress naming strings")),
		OPT_BOOL(0, "current", &with_current_branch,
			 N_("include the current branch")),
		OPT_BOOL(0, "sha1-name", &sha1_name,
			 N_("name commits with their object names")),
		OPT_BOOL(0, "merge-base", &merge_base,
			 N_("show possible merge bases")),
		OPT_BOOL(0, "independent", &independent,
			    N_("show refs unreachable from any other ref")),
		OPT_SET_INT(0, "topo-order", &sort_order,
			    N_("show commits in topological order"),
			    REV_SORT_IN_GRAPH_ORDER),
		OPT_BOOL(0, "topics", &topics,
			 N_("show only commits not on the first branch")),
		OPT_SET_INT(0, "sparse", &dense,
			    N_("show merges reachable from only one tip"), 0),
		OPT_SET_INT(0, "date-order", &sort_order,
			    N_("topologically sort, maintaining date order "
			       "where possible"),
			    REV_SORT_BY_COMMIT_DATE),
		{ OPTION_CALLBACK, 'g', "reflog", &reflog_base, N_("<n>[,<base>]"),
			    N_("show <n> most recent ref-log entries starting at "
			       "base"),
			    PARSE_OPT_OPTARG | PARSE_OPT_LITERAL_ARGHELP,
			    parse_reflog_param },
		OPT_END()
	};

	git_config(git_show_branch_config, NULL);

	/* If nothing is specified, try the default first */
	if (ac == 1 && default_args.argc) {
		ac = default_args.argc;
		av = default_args.argv;
	}

	ac = parse_options(ac, av, prefix, builtin_show_branch_options,
			   show_branch_usage, PARSE_OPT_STOP_AT_NON_OPTION);
	if (all_heads)
		all_remotes = 1;

	if (extra || reflog) {
		/* "listing" mode is incompatible with
		 * independent nor merge-base modes.
		 */
		if (independent || merge_base)
			usage_with_options(show_branch_usage,
					   builtin_show_branch_options);
		if (reflog && ((0 < extra) || all_heads || all_remotes))
			/*
			 * Asking for --more in reflog mode does not
			 * make sense.  --list is Ok.
			 *
			 * Also --all and --remotes do not make sense either.
			 */
			die(_("--reflog is incompatible with --all, --remotes, "
			      "--independent or --merge-base"));
	}

	/* If nothing is specified, show all branches by default */
	if (ac <= topics && all_heads + all_remotes == 0)
		all_heads = 1;

	if (reflog) {
		struct object_id oid;
		char *ref;
		int base = 0;
		unsigned int flags = 0;

		if (ac == 0) {
			static const char *fake_av[2];

			fake_av[0] = resolve_refdup("HEAD",
						    RESOLVE_REF_READING,
						    oid.hash, NULL);
			fake_av[1] = NULL;
			av = fake_av;
			ac = 1;
			if (!*av)
				die(_("no branches given, and HEAD is not valid"));
		}
		if (ac != 1)
			die(_("--reflog option needs one branch name"));

		if (MAX_REVS < reflog)
			die(Q_("only %d entry can be shown at one time.",
			       "only %d entries can be shown at one time.",
			       MAX_REVS), MAX_REVS);
		if (!dwim_ref(*av, strlen(*av), oid.hash, &ref))
			die(_("no such ref %s"), *av);

		/* Has the base been specified? */
		if (reflog_base) {
			char *ep;
			base = strtoul(reflog_base, &ep, 10);
			if (*ep) {
				/* Ah, that is a date spec... */
				timestamp_t at;
				at = approxidate(reflog_base);
				read_ref_at(ref, flags, at, -1, oid.hash, NULL,
					    NULL, NULL, &base);
			}
		}

		for (i = 0; i < reflog; i++) {
			char *logmsg;
			char *nth_desc;
			const char *msg;
			timestamp_t timestamp;
			int tz;

			if (read_ref_at(ref, flags, 0, base+i, oid.hash, &logmsg,
					&timestamp, &tz, NULL)) {
				reflog = i;
				break;
			}
			msg = strchr(logmsg, '\t');
			if (!msg)
				msg = "(none)";
			else
				msg++;
			reflog_msg[i] = xstrfmt("(%s) %s",
						show_date(timestamp, tz,
							  DATE_MODE(RELATIVE)),
						msg);
			free(logmsg);

			nth_desc = xstrfmt("%s@{%d}", *av, base+i);
			append_ref(nth_desc, &oid, 1);
			free(nth_desc);
		}
		free(ref);
	}
	else {
		while (0 < ac) {
			append_one_rev(*av);
			ac--; av++;
		}
		if (all_heads + all_remotes)
			snarf_refs(all_heads, all_remotes);
	}

	head = resolve_refdup("HEAD", RESOLVE_REF_READING,
			      head_oid.hash, NULL);

	if (with_current_branch && head) {
		int has_head = 0;
		for (i = 0; !has_head && i < ref_name_cnt; i++) {
			/* We are only interested in adding the branch
			 * HEAD points at.
			 */
			if (rev_is_head(head,
					ref_name[i],
					head_oid.hash, NULL))
				has_head++;
		}
		if (!has_head) {
			const char *name = head;
			skip_prefix(name, "refs/heads/", &name);
			append_one_rev(name);
		}
	}

	if (!ref_name_cnt) {
		fprintf(stderr, "No revs to be shown.\n");
		exit(0);
	}

	for (num_rev = 0; ref_name[num_rev]; num_rev++) {
		struct object_id revkey;
		unsigned int flag = 1u << (num_rev + REV_SHIFT);

		if (MAX_REVS <= num_rev)
			die(Q_("cannot handle more than %d rev.",
			       "cannot handle more than %d revs.",
			       MAX_REVS), MAX_REVS);
		if (get_sha1(ref_name[num_rev], revkey.hash))
			die(_("'%s' is not a valid ref."), ref_name[num_rev]);
		commit = lookup_commit_reference(&revkey);
		if (!commit)
			die(_("cannot find commit %s (%s)"),
			    ref_name[num_rev], oid_to_hex(&revkey));
		parse_commit(commit);
		mark_seen(commit, &seen);

		/* rev#0 uses bit REV_SHIFT, rev#1 uses bit REV_SHIFT+1,
		 * and so on.  REV_SHIFT bits from bit 0 are used for
		 * internal bookkeeping.
		 */
		commit->object.flags |= flag;
		if (commit->object.flags == flag)
			commit_list_insert_by_date(commit, &list);
		rev[num_rev] = commit;
	}
	for (i = 0; i < num_rev; i++)
		rev_mask[i] = rev[i]->object.flags;

	if (0 <= extra)
		join_revs(&list, &seen, num_rev, extra);

	commit_list_sort_by_date(&seen);

	if (merge_base)
		return show_merge_base(seen, num_rev);

	if (independent)
		return show_independent(rev, num_rev, ref_name, rev_mask);

	/* Show list; --more=-1 means list-only */
	if (1 < num_rev || extra < 0) {
		for (i = 0; i < num_rev; i++) {
			int j;
			int is_head = rev_is_head(head,
						  ref_name[i],
						  head_oid.hash,
						  rev[i]->object.oid.hash);
			if (extra < 0)
				printf("%c [%s] ",
				       is_head ? '*' : ' ', ref_name[i]);
			else {
				for (j = 0; j < i; j++)
					putchar(' ');
				printf("%s%c%s [%s] ",
				       get_color_code(i),
				       is_head ? '*' : '!',
				       get_color_reset_code(), ref_name[i]);
			}

			if (!reflog) {
				/* header lines never need name */
				show_one_commit(rev[i], 1);
			}
			else
				puts(reflog_msg[i]);

			if (is_head)
				head_at = i;
		}
		if (0 <= extra) {
			for (i = 0; i < num_rev; i++)
				putchar('-');
			putchar('\n');
		}
	}
	if (extra < 0)
		exit(0);

	/* Sort topologically */
	sort_in_topological_order(&seen, sort_order);

	/* Give names to commits */
	if (!sha1_name && !no_name)
		name_commits(seen, rev, ref_name, num_rev);

	all_mask = ((1u << (REV_SHIFT + num_rev)) - 1);
	all_revs = all_mask & ~((1u << REV_SHIFT) - 1);

	while (seen) {
		struct commit *commit = pop_commit(&seen);
		int this_flag = commit->object.flags;
		int is_merge_point = ((this_flag & all_revs) == all_revs);

		shown_merge_point |= is_merge_point;

		if (1 < num_rev) {
			int is_merge = !!(commit->parents &&
					  commit->parents->next);
			if (topics &&
			    !is_merge_point &&
			    (this_flag & (1u << REV_SHIFT)))
				continue;
			if (dense && is_merge &&
			    omit_in_dense(commit, rev, num_rev))
				continue;
			for (i = 0; i < num_rev; i++) {
				int mark;
				if (!(this_flag & (1u << (i + REV_SHIFT))))
					mark = ' ';
				else if (is_merge)
					mark = '-';
				else if (i == head_at)
					mark = '*';
				else
					mark = '+';
				printf("%s%c%s",
				       get_color_code(i),
				       mark, get_color_reset_code());
			}
			putchar(' ');
		}
		show_one_commit(commit, no_name);

		if (shown_merge_point && --extra < 0)
			break;
	}
	return 0;
}