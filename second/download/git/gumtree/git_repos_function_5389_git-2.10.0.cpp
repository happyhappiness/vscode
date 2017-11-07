static void remove_junk(void)
{
	struct strbuf sb = STRBUF_INIT;

	switch (junk_mode) {
	case JUNK_LEAVE_REPO:
		warning("%s", _(junk_leave_repo_msg));
		/* fall-through */
	case JUNK_LEAVE_ALL:
		return;
	default:
		/* proceed to removal */
		break;
	}

	if (junk_git_dir) {
		strbuf_addstr(&sb, junk_git_dir);
		remove_dir_recursively(&sb, 0);
		strbuf_reset(&sb);
	}
	if (junk_work_tree) {
		strbuf_addstr(&sb, junk_work_tree);
		remove_dir_recursively(&sb, 0);
		strbuf_reset(&sb);
	}
}