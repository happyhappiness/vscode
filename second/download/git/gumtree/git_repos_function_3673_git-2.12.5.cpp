void graph_show_commit_msg(struct git_graph *graph,
			   FILE *file,
			   struct strbuf const *sb)
{
	int newline_terminated;

	/*
	 * Show the commit message
	 */
	graph_show_strbuf(graph, file, sb);

	if (!graph)
		return;

	newline_terminated = (sb->len && sb->buf[sb->len - 1] == '\n');

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
			putc('\n', file);

		graph_show_remainder(graph);

		/*
		 * If sb ends with a newline, our output should too.
		 */
		if (newline_terminated)
			putc('\n', file);
	}
}