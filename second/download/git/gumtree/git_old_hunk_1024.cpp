	 * the .git/NOTES_MERGE_WORKTREE directory itself, since it might be
	 * the current working directory of the user.
	 */
	struct strbuf buf = STRBUF_INIT;
	int ret;

	strbuf_addstr(&buf, git_path(NOTES_MERGE_WORKTREE));
	if (o->verbosity >= 3)
		printf("Removing notes merge worktree at %s/*\n", buf.buf);
	ret = remove_dir_recursively(&buf, REMOVE_DIR_KEEP_TOPLEVEL);
	strbuf_release(&buf);
	return ret;
}
