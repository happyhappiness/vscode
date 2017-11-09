static void graph_output_pre_commit_line(struct git_graph *graph,
					 struct strbuf *sb)
{
	int num_expansion_rows;
	int i, seen_this;
	int chars_written;

	/*
	 * This function formats a row that increases the space around a commit
	 * with multiple parents, to make room for it.  It should only be
	 * called when there are 3 or more parents.
	 *
	 * We need 2 extra rows for every parent over 2.
	 */
	assert(graph->num_parents >= 3);
	num_expansion_rows = (graph->num_parents - 2) * 2;

	/*
	 * graph->expansion_row tracks the current expansion row we are on.
	 * It should be in the range [0, num_expansion_rows - 1]
	 */
	assert(0 <= graph->expansion_row &&
	       graph->expansion_row < num_expansion_rows);

	/*
	 * Output the row
	 */
	seen_this = 0;
	chars_written = 0;
	for (i = 0; i < graph->num_columns; i++) {
		struct column *col = &graph->columns[i];
		if (col->commit == graph->commit) {
			seen_this = 1;
			strbuf_write_column(sb, col, '|');
			strbuf_addf(sb, "%*s", graph->expansion_row, "");
			chars_written += 1 + graph->expansion_row;
		} else if (seen_this && (graph->expansion_row == 0)) {
			/*
			 * This is the first line of the pre-commit output.
			 * If the previous commit was a merge commit and
			 * ended in the GRAPH_POST_MERGE state, all branch
			 * lines after graph->prev_commit_index were
			 * printed as "\" on the previous line.  Continue
			 * to print them as "\" on this line.  Otherwise,
			 * print the branch lines as "|".
			 */
			if (graph->prev_state == GRAPH_POST_MERGE &&
			    graph->prev_commit_index < i)
				strbuf_write_column(sb, col, '\\');
			else
				strbuf_write_column(sb, col, '|');
			chars_written++;
		} else if (seen_this && (graph->expansion_row > 0)) {
			strbuf_write_column(sb, col, '\\');
			chars_written++;
		} else {
			strbuf_write_column(sb, col, '|');
			chars_written++;
		}
		strbuf_addch(sb, ' ');
		chars_written++;
	}

	graph_pad_horizontally(graph, sb, chars_written);

	/*
	 * Increment graph->expansion_row,
	 * and move to state GRAPH_COMMIT if necessary
	 */
	graph->expansion_row++;
	if (graph->expansion_row >= num_expansion_rows)
		graph_update_state(graph, GRAPH_COMMIT);
}