void graph_show_commit(struct git_graph *graph)
{
	struct strbuf msgbuf = STRBUF_INIT;
	int shown_commit_line = 0;

	graph_show_line_prefix(default_diffopt);

	if (!graph)
		return;

	/*
	 * When showing a diff of a merge against each of its parents, we
	 * are called once for each parent without graph_update having been
	 * called.  In this case, simply output a single padding line.
	 */
	if (graph_is_commit_finished(graph)) {
		graph_show_padding(graph);
		shown_commit_line = 1;
	}

	while (!shown_commit_line && !graph_is_commit_finished(graph)) {
		shown_commit_line = graph_next_line(graph, &msgbuf);
		fwrite(msgbuf.buf, sizeof(char), msgbuf.len,
			graph->revs->diffopt.file);
		if (!shown_commit_line) {
			putc('\n', graph->revs->diffopt.file);
			graph_show_line_prefix(&graph->revs->diffopt);
		}
		strbuf_setlen(&msgbuf, 0);
	}

	strbuf_release(&msgbuf);
}