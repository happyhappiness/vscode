static unsigned short graph_get_current_column_color(const struct git_graph *graph)
{
	if (!want_color(graph->revs->diffopt.use_color))
		return column_colors_max;
	return graph->default_column_color;
}