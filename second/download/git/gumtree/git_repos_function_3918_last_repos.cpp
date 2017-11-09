static unsigned short graph_find_commit_color(const struct git_graph *graph,
					      const struct commit *commit)
{
	int i;
	for (i = 0; i < graph->num_columns; i++) {
		if (graph->columns[i].commit == commit)
			return graph->columns[i].color;
	}
	return graph_get_current_column_color(graph);
}