static void graph_update_state(struct git_graph *graph, enum graph_state s)
{
	graph->prev_state = graph->state;
	graph->state = s;
}