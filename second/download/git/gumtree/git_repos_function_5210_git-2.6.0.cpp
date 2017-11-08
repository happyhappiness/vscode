static int add_worktree(const char *path, const char *refname,
			const struct add_opts *opts)
{
	struct strbuf sb_git = STRBUF_INIT, sb_repo = STRBUF_INIT;
	struct strbuf sb = STRBUF_INIT;
	const char *name;
	struct stat st;
	struct child_process cp;
	struct argv_array child_env = ARGV_ARRAY_INIT;
	int counter = 0, len, ret;
	struct strbuf symref = STRBUF_INIT;
	struct commit *commit = NULL;

	if (file_exists(path) && !is_empty_dir(path))
		die(_("'%s' already exists"), path);

	/* is 'refname' a branch or commit? */
	if (opts->force_new_branch) /* definitely a branch */
		;
	else if (!opts->detach && !strbuf_check_branch_ref(&symref, refname) &&
		 ref_exists(symref.buf)) { /* it's a branch */
		if (!opts->force)
			die_if_checked_out(symref.buf);
	} else { /* must be a commit */
		commit = lookup_commit_reference_by_name(refname);
		if (!commit)
			die(_("invalid reference: %s"), refname);
	}

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