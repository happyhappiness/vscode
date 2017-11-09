static void graph_output_skip_line(struct git_graph *graph, struct strbuf *sb)
{
	/*
	 * Output an ellipsis to indicate that a portion
	 * of the graph is missing.
	 */
	strbuf_addstr(sb, "...");
	graph_pad_horizontally(graph, sb, 3);

	if (graph->num_parents >= 3 &&
	    graph->commit_index < (graph->num_columns - 1))
		graph_update_state(graph, GRAPH_PRE_COMMIT);
	else
		graph_update_state(graph, GRAPH_COMMIT);
}