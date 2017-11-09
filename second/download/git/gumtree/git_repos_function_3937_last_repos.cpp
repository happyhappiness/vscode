int graph_is_commit_finished(struct git_graph const *graph)
{
	return (graph->state == GRAPH_PADDING);
}