static void graph_pad_horizontally(struct git_graph *graph, struct strbuf *sb,
				   int chars_written)
{
	/*
	 * Add additional spaces to the end of the strbuf, so that all
	 * lines for a particular commit have the same width.
	 *
	 * This way, fields printed to the right of the graph will remain
	 * aligned for the entire commit.
	 */
	int extra;
	if (chars_written >= graph->width)
		return;

	extra = graph->width - chars_written;
	strbuf_addf(sb, "%*s", (int) extra, "");
}