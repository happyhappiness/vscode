static int add_worktree(const char *path, const char **child_argv)
{
	struct strbuf sb_git = STRBUF_INIT, sb_repo = STRBUF_INIT;
	struct strbuf sb = STRBUF_INIT;
	const char *name;
	struct stat st;
	struct child_process cp;
	int counter = 0, len, ret;
	unsigned char rev[20];

	if (file_exists(path) && !is_empty_dir(path))
		die(_("'%s' already exists"), path);

	name = worktree_basename(path, &len);
	strbuf_addstr(&sb_repo,
		      git_path("worktrees/%.*s", (int)(path + len - name), name));
	len = sb_repo.len;
	if (safe_create_leading_directories_const(sb_repo.buf))
		die_errno(_("could not create leading directories of '%s'"),
			  sb_repo.buf);
	while (!stat(sb_repo.buf, &st)) {
		counter++;
		strbuf_setlen(&sb_repo, len);
		strbuf_addf(&sb_repo, "%d", counter);
	}
	name = strrchr(sb_repo.buf, '/') + 1;

	junk_pid = getpid();
	atexit(remove_junk);
	sigchain_push_common(remove_junk_on_signal);

	if (mkdir(sb_repo.buf, 0777))
		die_errno(_("could not create directory of '%s'"), sb_repo.buf);
	junk_git_dir = xstrdup(sb_repo.buf);
	is_junk = 1;

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