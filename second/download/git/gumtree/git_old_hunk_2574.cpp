
	/*
	 * lock the incomplete repo so prune won't delete it, unlock
	 * after the preparation is over.
	 */
	strbuf_addf(&sb, "%s/locked", sb_repo.buf);
	write_file(sb.buf, 1, "initializing\n");

	strbuf_addf(&sb_git, "%s/.git", path);
	if (safe_create_leading_directories_const(sb_git.buf))
		die_errno(_("could not create leading directories of '%s'"),
			  sb_git.buf);
	junk_work_tree = xstrdup(path);

	strbuf_reset(&sb);
	strbuf_addf(&sb, "%s/gitdir", sb_repo.buf);
	write_file(sb.buf, 1, "%s\n", real_path(sb_git.buf));
	write_file(sb_git.buf, 1, "gitdir: %s/worktrees/%s\n",
		   real_path(get_git_common_dir()), name);
	/*
	 * This is to keep resolve_ref() happy. We need a valid HEAD
	 * or is_git_directory() will reject the directory. Moreover, HEAD
	 * in the new worktree must resolve to the same value as HEAD in
	 * the current tree since the command invoked to populate the new
	 * worktree will be handed the branch/ref specified by the user.
	 * For instance, if the user asks for the new worktree to be based
	 * at HEAD~5, then the resolved HEAD~5 in the new worktree must
	 * match the resolved HEAD~5 in the current tree in order to match
	 * the user's expectation.
	 */
	if (!resolve_ref_unsafe("HEAD", 0, rev, NULL))
		die(_("unable to resolve HEAD"));
	strbuf_reset(&sb);
	strbuf_addf(&sb, "%s/HEAD", sb_repo.buf);
	write_file(sb.buf, 1, "%s\n", sha1_to_hex(rev));
	strbuf_reset(&sb);
	strbuf_addf(&sb, "%s/commondir", sb_repo.buf);
	write_file(sb.buf, 1, "../..\n");

	fprintf_ln(stderr, _("Enter %s (identifier %s)"), path, name);

	setenv("GIT_CHECKOUT_NEW_WORKTREE", "1", 1);
	setenv(GIT_DIR_ENVIRONMENT, sb_git.buf, 1);
	setenv(GIT_WORK_TREE_ENVIRONMENT, path, 1);
	memset(&cp, 0, sizeof(cp));
	cp.git_cmd = 1;
	cp.argv = child_argv;
	ret = run_command(&cp);
	if (!ret) {
		is_junk = 0;
		free(junk_work_tree);
		free(junk_git_dir);
		junk_work_tree = NULL;
		junk_git_dir = NULL;
	}
	strbuf_reset(&sb);
	strbuf_addf(&sb, "%s/locked", sb_repo.buf);
	unlink_or_warn(sb.buf);
	strbuf_release(&sb);
	strbuf_release(&sb_repo);
	strbuf_release(&sb_git);
	return ret;
}

static int add(int ac, const char **av, const char *prefix)
{
	int force = 0, detach = 0;
	const char *new_branch = NULL, *new_branch_force = NULL;
	const char *path, *branch;
	struct argv_array cmd = ARGV_ARRAY_INIT;
	struct option options[] = {
		OPT__FORCE(&force, N_("checkout <branch> even if already checked out in other worktree")),
		OPT_STRING('b', NULL, &new_branch, N_("branch"),
			   N_("create a new branch")),
		OPT_STRING('B', NULL, &new_branch_force, N_("branch"),
			   N_("create or reset a branch")),
		OPT_BOOL(0, "detach", &detach, N_("detach HEAD at named commit")),
		OPT_END()
	};

	ac = parse_options(ac, av, prefix, options, worktree_usage, 0);
	if (new_branch && new_branch_force)
		die(_("-b and -B are mutually exclusive"));
	if (ac < 1 || ac > 2)
		usage_with_options(worktree_usage, options);

	path = prefix ? prefix_filename(prefix, strlen(prefix), av[0]) : av[0];
	branch = ac < 2 ? "HEAD" : av[1];

	if (ac < 2 && !new_branch && !new_branch_force) {
		int n;
		const char *s = worktree_basename(path, &n);
		new_branch = xstrndup(s, n);
	}

	argv_array_push(&cmd, "checkout");
	if (force)
		argv_array_push(&cmd, "--ignore-other-worktrees");
	if (new_branch)
		argv_array_pushl(&cmd, "-b", new_branch, NULL);
	if (new_branch_force)
		argv_array_pushl(&cmd, "-B", new_branch_force, NULL);
	if (detach)
		argv_array_push(&cmd, "--detach");
	argv_array_push(&cmd, branch);

	return add_worktree(path, cmd.argv);
}

int cmd_worktree(int ac, const char **av, const char *prefix)
{
	struct option options[] = {
		OPT_END()
