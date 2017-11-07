void graph_show_padding(struct git_graph *graph)
{
	struct strbuf msgbuf = STRBUF_INIT;

	if (!graph)
		return;

	graph_padding_line(graph, &msgbuf);
	fwrite(msgbuf.buf, sizeof(char), msgbuf.len, graph->revs->diffopt.file);
	strbuf_release(&msgbuf);
}