static void parse_graph_colors_config(struct argv_array *colors, const char *string)
{
	const char *end, *start;

	start = string;
	end = string + strlen(string);
	while (start < end) {
		const char *comma = strchrnul(start, ',');
		char color[COLOR_MAXLEN];

		if (!color_parse_mem(start, comma - start, color))
			argv_array_push(colors, color);
		else
			warning(_("ignore invalid color '%.*s' in log.graphColors"),
				(int)(comma - start), start);
		start = comma + 1;
	}
	argv_array_push(colors, GIT_COLOR_RESET);
}