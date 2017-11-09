static struct strbuf *diff_output_prefix_callback(struct diff_options *opt, void *data)
{
	struct git_graph *graph = data;
	static struct strbuf msgbuf = STRBUF_INIT;

	assert(opt);

	strbuf_reset(&msgbuf);
	if (opt->line_prefix)
		strbuf_add(&msgbuf, opt->line_prefix,
			   opt->line_prefix_length);
	if (graph)
		graph_padding_line(graph, &msgbuf);
	return &msgbuf;
}