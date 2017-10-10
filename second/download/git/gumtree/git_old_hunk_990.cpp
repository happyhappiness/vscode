	free(junk_work_tree);
	free(junk_git_dir);
	junk_work_tree = NULL;
	junk_git_dir = NULL;

done:
	strbuf_reset(&sb);
	strbuf_addf(&sb, "%s/locked", sb_repo.buf);
	unlink_or_warn(sb.buf);
	argv_array_clear(&child_env);
	strbuf_release(&sb);
	strbuf_release(&symref);
	strbuf_release(&sb_repo);
	strbuf_release(&sb_git);
	return ret;
}

static int add(int ac, const char **av, const char *prefix)
{
	struct add_opts opts;
	const char *new_branch_force = NULL;
	const char *path, *branch;
	struct option options[] = {
		OPT__FORCE(&opts.force, N_("checkout <branch> even if already checked out in other worktree")),
		OPT_STRING('b', NULL, &opts.new_branch, N_("branch"),
			   N_("create a new branch")),
		OPT_STRING('B', NULL, &new_branch_force, N_("branch"),
			   N_("create or reset a branch")),
		OPT_BOOL(0, "detach", &opts.detach, N_("detach HEAD at named commit")),
		OPT_BOOL(0, "checkout", &opts.checkout, N_("populate the new working tree")),
		OPT_END()
	};

	memset(&opts, 0, sizeof(opts));
	opts.checkout = 1;
	ac = parse_options(ac, av, prefix, options, worktree_usage, 0);
	if (!!opts.detach + !!opts.new_branch + !!new_branch_force > 1)
		die(_("-b, -B, and --detach are mutually exclusive"));
	if (ac < 1 || ac > 2)
		usage_with_options(worktree_usage, options);

	path = prefix_filename(prefix, strlen(prefix), av[0]);
	branch = ac < 2 ? "HEAD" : av[1];

	if (!strcmp(branch, "-"))
		branch = "@{-1}";

	opts.force_new_branch = !!new_branch_force;
