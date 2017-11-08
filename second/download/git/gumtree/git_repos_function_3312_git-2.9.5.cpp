static void graph_output_padding_line(struct git_graph *graph,
				      struct strbuf *sb)
{
	int i;

	/*
	 * We could conceivable be called with a NULL commit
	 * if our caller has a bug, and invokes graph_next_line()
	 * immediately after graph_init(), without first calling
	 * graph_update().  Return without outputting anything in this
	 * case.
	 */
	if (!graph->commit)
		return;

	/*
	 * Output a padding row, that leaves all branch lines unchanged
	 */
	for (i = 0; i < graph->num_new_columns; i++) {
		strbuf_write_column(sb, &graph->new_columns[i], '|');
		strbuf_addch(sb, ' ');
	}

	graph_pad_horizontally(graph, sb, graph->num_new_columns * 2);
}