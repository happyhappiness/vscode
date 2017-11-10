int graph_show_remainder(struct git_graph *graph)
{
	struct strbuf msgbuf = STRBUF_INIT;
	int shown = 0;

	graph_show_line_prefix(default_diffopt);

	if (!graph)
		return 0;

	if (graph_is_commit_finished(graph))
		return 0;

	for (;;) {
		graph_next_line(graph, &msgbuf);
		fwrite(msgbuf.buf, sizeof(char), msgbuf.len,
			graph->revs->diffopt.file);
		strbuf_setlen(&msgbuf, 0);
		shown = 1;

		if (!graph_is_commit_finished(graph)) {
			putc('\n', graph->revs->diffopt.file);
			graph_show_line_prefix(&graph->revs->diffopt);
		} else {
			break;
		}
	}
	strbuf_release(&msgbuf);

	return shown;
}