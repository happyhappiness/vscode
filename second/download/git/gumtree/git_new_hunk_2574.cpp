
	/*
	 * lock the incomplete repo so prune won't delete it, unlock
	 * after the preparation is over.
	 */
	strbuf_addf(&sb, "%s/locked", sb_repo.buf);
	write_file(sb.buf, "initializing");

	strbuf_addf(&sb_git, "%s/.git", path);
	if (safe_create_leading_directories_const(sb_git.buf))
		die_errno(_("could not create leading directories of '%s'"),
			  sb_git.buf);
	junk_work_tree = xstrdup(path);

	strbuf_reset(&sb);
	strbuf_addf(&sb, "%s/gitdir", sb_repo.buf);
	write_file(sb.buf, "%s", real_path(sb_git.buf));
	write_file(sb_git.buf, "gitdir: %s/worktrees/%s",
		   real_path(get_git_common_dir()), name);
	/*
	 * This is to keep resolve_ref() happy. We need a valid HEAD
	 * or is_git_directory() will reject the directory. Any value which
	 * looks like an object ID will do since it will be immediately
	 * replaced by the symbolic-ref or update-ref invocation in the new
	 * worktree.
	 */
	strbuf_reset(&sb);
	strbuf_addf(&sb, "%s/HEAD", sb_repo.buf);
	write_file(sb.buf, "0000000000000000000000000000000000000000");
	strbuf_reset(&sb);
	strbuf_addf(&sb, "%s/commondir", sb_repo.buf);
	write_file(sb.buf, "../..");

	fprintf_ln(stderr, _("Preparing %s (identifier %s)"), path, name);

	argv_array_pushf(&child_env, "%s=%s", GIT_DIR_ENVIRONMENT, sb_git.buf);
	argv_array_pushf(&child_env, "%s=%s", GIT_WORK_TREE_ENVIRONMENT, path);
	memset(&cp, 0, sizeof(cp));
	cp.git_cmd = 1;

	if (commit)
		argv_array_pushl(&cp.args, "update-ref", "HEAD",
				 sha1_to_hex(commit->object.sha1), NULL);
	else
		argv_array_pushl(&cp.args, "symbolic-ref", "HEAD",
				 symref.buf, NULL);
	cp.env = child_env.argv;
	ret = run_command(&cp);
	if (ret)
		goto done;

	cp.argv = NULL;
	argv_array_clear(&cp.args);
	argv_array_pushl(&cp.args, "reset", "--hard", NULL);
	cp.env = child_env.argv;
	ret = run_command(&cp);
	if (!ret) {
		is_junk = 0;
		free(junk_work_tree);
		free(junk_git_dir);
		junk_work_tree = NULL;
		junk_git_dir = NULL;
	}
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
		OPT_END()
	};

	memset(&opts, 0, sizeof(opts));
	ac = parse_options(ac, av, prefix, options, worktree_usage, 0);
	if (!!opts.detach + !!opts.new_branch + !!new_branch_force > 1)
		die(_("-b, -B, and --detach are mutually exclusive"));
	if (ac < 1 || ac > 2)
		usage_with_options(worktree_usage, options);

	path = prefix ? prefix_filename(prefix, strlen(prefix), av[0]) : av[0];
	branch = ac < 2 ? "HEAD" : av[1];

	opts.force_new_branch = !!new_branch_force;
	if (opts.force_new_branch)
		opts.new_branch = new_branch_force;

	if (ac < 2 && !opts.new_branch && !opts.detach) {
		int n;
		const char *s = worktree_basename(path, &n);
		opts.new_branch = xstrndup(s, n);
	}

	if (opts.new_branch) {
		struct child_process cp;
		memset(&cp, 0, sizeof(cp));
		cp.git_cmd = 1;
		argv_array_push(&cp.args, "branch");
		if (opts.force_new_branch)
			argv_array_push(&cp.args, "--force");
		argv_array_push(&cp.args, opts.new_branch);
		argv_array_push(&cp.args, branch);
		if (run_command(&cp))
			return -1;
		branch = opts.new_branch;
	}

	return add_worktree(path, branch, &opts);
}

int cmd_worktree(int ac, const char **av, const char *prefix)
{
	struct option options[] = {
		OPT_END()
