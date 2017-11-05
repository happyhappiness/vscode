static struct strbuf *diff_output_prefix_callback(struct diff_options *opt, void *data)
{
	struct git_graph *graph = data;
	static struct strbuf msgbuf = STRBUF_INIT;

	assert(opt);
	assert(graph);

	opt->output_prefix_length = graph->width;
	strbuf_reset(&msgbuf);
	graph_padding_line(graph, &msgbuf);
	return &msgbuf;
}