void graph_show_commit_msg(struct git_graph *graph,
			   struct strbuf const *sb)
{
	int newline_terminated;

	if (!graph) {
		/*
		 * If there's no graph, just print the message buffer.
		 *
		 * The message buffer for CMIT_FMT_ONELINE and
		 * CMIT_FMT_USERFORMAT are already missing a terminating
		 * newline.  All of the other formats should have it.
		 */
		fwrite(sb->buf, sizeof(char), sb->len, stdout);
		return;
	}

	newline_terminated = (sb->len && sb->buf[sb->len - 1] == '\n');

	/*
	 * Show the commit message
	 */
	graph_show_strbuf(graph, sb);

	/*
	 * If there is more output needed for this commit, show it now
	 */
	if (!graph_is_commit_finished(graph)) {
		/*
		 * If sb doesn't have a terminating newline, print one now,
		 * so we can start the remainder of the graph output on a
		 * new line.
		 */
		if (!newline_terminated)
			putchar('\n');

		graph_show_remainder(graph);

		/*
		 * If sb ends with a newline, our output should too.
		 */
		if (newline_terminated)
			putchar('\n');
	}
}