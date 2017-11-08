static void prepare_to_commit(struct commit_list *remoteheads)
{
	struct strbuf msg = STRBUF_INIT;
	strbuf_addbuf(&msg, &merge_msg);
	strbuf_addch(&msg, '\n');
	if (0 < option_edit)
		strbuf_commented_addf(&msg, _(merge_editor_comment), comment_line_char);
	write_merge_msg(&msg);
	if (run_commit_hook(0 < option_edit, get_index_file(), "prepare-commit-msg",
			    git_path("MERGE_MSG"), "merge", NULL))
		abort_commit(remoteheads, NULL);
	if (0 < option_edit) {
		if (launch_editor(git_path("MERGE_MSG"), NULL, NULL))
			abort_commit(remoteheads, NULL);
	}
	read_merge_msg(&msg);
	stripspace(&msg, 0 < option_edit);
	if (!msg.len)
		abort_commit(remoteheads, _("Empty commit message."));
	strbuf_release(&merge_msg);
	strbuf_addbuf(&merge_msg, &msg);
	strbuf_release(&msg);
}