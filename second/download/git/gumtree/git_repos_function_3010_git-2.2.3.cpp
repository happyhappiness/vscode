static void graph_show_strbuf(struct git_graph *graph, struct strbuf const *sb)
{
	char *p;

	if (!graph) {
		fwrite(sb->buf, sizeof(char), sb->len, stdout);
		return;
	}

	/*
	 * Print the strbuf line by line,
	 * and display the graph info before each line but the first.
	 */
	p = sb->buf;
	while (p) {
		size_t len;
		char *next_p = strchr(p, '\n');
		if (next_p) {
			next_p++;
			len = next_p - p;
		} else {
			len = (sb->buf + sb->len) - p;
		}
		fwrite(p, sizeof(char), len, stdout);
		if (next_p && *next_p != '\0')
			graph_show_oneline(graph);
		p = next_p;
	}
}