struct git_graph *graph_init(struct rev_info *opt)
{
	struct git_graph *graph = xmalloc(sizeof(struct git_graph));

	if (!column_colors) {
		char *string;
		if (git_config_get_string("log.graphcolors", &string)) {
			/* not configured -- use default */
			graph_set_column_colors(column_colors_ansi,
						column_colors_ansi_max);
		} else {
			static struct argv_array custom_colors = ARGV_ARRAY_INIT;
			argv_array_clear(&custom_colors);
			parse_graph_colors_config(&custom_colors, string);
			free(string);
			/* graph_set_column_colors takes a max-index, not a count */
			graph_set_column_colors(custom_colors.argv,
						custom_colors.argc - 1);
		}
	}

	graph->commit = NULL;
	graph->revs = opt;
	graph->num_parents = 0;
	graph->expansion_row = 0;
	graph->state = GRAPH_PADDING;
	graph->prev_state = GRAPH_PADDING;
	graph->commit_index = 0;
	graph->prev_commit_index = 0;
	graph->num_columns = 0;
	graph->num_new_columns = 0;
	graph->mapping_size = 0;
	/*
	 * Start the column color at the maximum value, since we'll
	 * always increment it for the first commit we output.
	 * This way we start at 0 for the first commit.
	 */
	graph->default_column_color = column_colors_max - 1;

	/*
	 * Allocate a reasonably large default number of columns
	 * We'll automatically grow columns later if we need more room.
	 */
	graph->column_capacity = 30;
	ALLOC_ARRAY(graph->columns, graph->column_capacity);
	ALLOC_ARRAY(graph->new_columns, graph->column_capacity);
	ALLOC_ARRAY(graph->mapping, 2 * graph->column_capacity);
	ALLOC_ARRAY(graph->new_mapping, 2 * graph->column_capacity);

	/*
	 * The diff output prefix callback, with this we can make
	 * all the diff output to align with the graph lines.
	 */
	opt->diffopt.output_prefix = diff_output_prefix_callback;
	opt->diffopt.output_prefix_data = graph;

	return graph;
}