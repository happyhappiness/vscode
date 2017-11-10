int graph_next_line(struct git_graph *graph, struct strbuf *sb)
{
	switch (graph->state) {
	case GRAPH_PADDING:
		graph_output_padding_line(graph, sb);
		return 0;
	case GRAPH_SKIP:
		graph_output_skip_line(graph, sb);
		return 0;
	case GRAPH_PRE_COMMIT:
		graph_output_pre_commit_line(graph, sb);
		return 0;
	case GRAPH_COMMIT:
		graph_output_commit_line(graph, sb);
		return 1;
	case GRAPH_POST_MERGE:
		graph_output_post_merge_line(graph, sb);
		return 0;
	case GRAPH_COLLAPSING:
		graph_output_collapsing_line(graph, sb);
		return 0;
	}

	assert(0);
	return 0;
}