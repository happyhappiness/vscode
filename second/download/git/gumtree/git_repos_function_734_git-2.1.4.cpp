static void wt_status_print_submodule_summary(struct wt_status *s, int uncommitted)
{
	struct child_process sm_summary;
	struct argv_array env = ARGV_ARRAY_INIT;
	struct argv_array argv = ARGV_ARRAY_INIT;
	struct strbuf cmd_stdout = STRBUF_INIT;
	struct strbuf summary = STRBUF_INIT;
	char *summary_content;
	size_t len;

	argv_array_pushf(&env, "GIT_INDEX_FILE=%s", s->index_file);

	argv_array_push(&argv, "submodule");
	argv_array_push(&argv, "summary");
	argv_array_push(&argv, uncommitted ? "--files" : "--cached");
	argv_array_push(&argv, "--for-status");
	argv_array_push(&argv, "--summary-limit");
	argv_array_pushf(&argv, "%d", s->submodule_summary);
	if (!uncommitted)
		argv_array_push(&argv, s->amend ? "HEAD^" : "HEAD");

	memset(&sm_summary, 0, sizeof(sm_summary));
	sm_summary.argv = argv.argv;
	sm_summary.env = env.argv;
	sm_summary.git_cmd = 1;
	sm_summary.no_stdin = 1;
	fflush(s->fp);
	sm_summary.out = -1;

	run_command(&sm_summary);
	argv_array_clear(&env);
	argv_array_clear(&argv);

	len = strbuf_read(&cmd_stdout, sm_summary.out, 1024);

	/* prepend header, only if there's an actual output */
	if (len) {
		if (uncommitted)
			strbuf_addstr(&summary, _("Submodules changed but not updated:"));
		else
			strbuf_addstr(&summary, _("Submodule changes to be committed:"));
		strbuf_addstr(&summary, "\n\n");
	}
	strbuf_addbuf(&summary, &cmd_stdout);
	strbuf_release(&cmd_stdout);

	if (s->display_comment_prefix) {
		summary_content = strbuf_detach(&summary, &len);
		strbuf_add_commented_lines(&summary, summary_content, len);
		free(summary_content);
	}

	fputs(summary.buf, s->fp);
	strbuf_release(&summary);
}