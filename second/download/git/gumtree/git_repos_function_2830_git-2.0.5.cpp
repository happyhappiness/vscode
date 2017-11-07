static void graph_padding_line(struct git_graph *graph, struct strbuf *sb)
{
	int i, j;

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
		struct commit *col_commit = col->commit;
		if (col_commit == graph->commit) {
			strbuf_write_column(sb, col, '|');

			if (graph->num_parents < 3)
				strbuf_addch(sb, ' ');
			else {
				int num_spaces = ((graph->num_parents - 2) * 2);
				for (j = 0; j < num_spaces; j++)
					strbuf_addch(sb, ' ');
			}
		} else {
			strbuf_write_column(sb, col, '|');
			strbuf_addch(sb, ' ');
		}
	}

	graph_pad_horizontally(graph, sb, graph->num_columns);

	/*
	 * Update graph->prev_state since we have output a padding line
	 */
	graph->prev_state = GRAPH_PADDING;
}