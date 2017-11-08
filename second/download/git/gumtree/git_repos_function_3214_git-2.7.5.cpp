static void graph_ensure_capacity(struct git_graph *graph, int num_columns)
{
	if (graph->column_capacity >= num_columns)
		return;

	do {
		graph->column_capacity *= 2;
	} while (graph->column_capacity < num_columns);

	REALLOC_ARRAY(graph->columns, graph->column_capacity);
	REALLOC_ARRAY(graph->new_columns, graph->column_capacity);
	REALLOC_ARRAY(graph->mapping, graph->column_capacity * 2);
	REALLOC_ARRAY(graph->new_mapping, graph->column_capacity * 2);
}