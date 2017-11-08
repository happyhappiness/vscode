static void graph_padding_line(struct git_graph *graph, struct strbuf *sb)
{
	int i;

	if (graph->state != GRAPH_COMMIT) {
		graph_next_line(graph, sb);
		return;
	}

	/*
	 * Output the row containing this commit
	 * Iterate up to and including graph->num_columns,
	 * since the current commit may not be in any of the existing
	 * columns.  (This happens when the current commit doesn't have any
	 * children that we have already processed.)
	 */
	for (i = 0; i < graph->num_columns; i++) {
		struct column *col = &graph->columns[i];
		strbuf_write_column(sb, col, '|');
		if (col->commit == graph->commit && graph->num_parents > 2)
			strbuf_addchars(sb, ' ', (graph->num_parents - 2) * 2);
		else
			strbuf_addch(sb, ' ');
	}

	graph_pad_horizontally(graph, sb, graph->num_columns);

	/*
	 * Update graph->prev_state since we have output a padding line
	 */
	graph->prev_state = GRAPH_PADDING;
}