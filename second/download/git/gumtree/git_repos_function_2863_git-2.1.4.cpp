static void graph_ensure_capacity(struct git_graph *graph, int num_columns)
{
	if (graph->column_capacity >= num_columns)
		return;

	do {
		graph->column_capacity *= 2;
	} while (graph->column_capacity < num_columns);

	graph->columns = xrealloc(graph->columns,
				  sizeof(struct column) *
				  graph->column_capacity);
	graph->new_columns = xrealloc(graph->new_columns,
				      sizeof(struct column) *
				      graph->column_capacity);
	graph->mapping = xrealloc(graph->mapping,
				  sizeof(int) * 2 * graph->column_capacity);
	graph->new_mapping = xrealloc(graph->new_mapping,
				      sizeof(int) * 2 * graph->column_capacity);
}