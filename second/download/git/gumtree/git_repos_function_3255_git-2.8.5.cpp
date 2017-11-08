static void graph_increment_column_color(struct git_graph *graph)
{
	graph->default_column_color = (graph->default_column_color + 1) %
		column_colors_max;
}