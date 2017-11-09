static void graph_output_commit_char(struct git_graph *graph, struct strbuf *sb)
{
	/*
	 * For boundary commits, print 'o'
	 * (We should only see boundary commits when revs->boundary is set.)
	 */
	if (graph->commit->object.flags & BOUNDARY) {
		assert(graph->revs->boundary);
		strbuf_addch(sb, 'o');
		return;
	}

	/*
	 * get_revision_mark() handles all other cases without assert()
	 */
	strbuf_addstr(sb, get_revision_mark(graph->revs, graph->commit));
}