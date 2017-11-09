void graph_show_oneline(struct git_graph *graph)
{
	struct strbuf msgbuf = STRBUF_INIT;

	graph_show_line_prefix(default_diffopt);

	if (!graph)
		return;

	graph_next_line(graph, &msgbuf);
	fwrite(msgbuf.buf, sizeof(char), msgbuf.len, graph->revs->diffopt.file);
	strbuf_release(&msgbuf);
}