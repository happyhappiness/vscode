int graph_show_remainder(struct git_graph *graph)
{
	struct strbuf msgbuf = STRBUF_INIT;
	int shown = 0;

	if (!graph)
		return 0;

	if (graph_is_commit_finished(graph))
		return 0;

	for (;;) {
		graph_next_line(graph, &msgbuf);
		fwrite(msgbuf.buf, sizeof(char), msgbuf.len, stdout);
		strbuf_setlen(&msgbuf, 0);
		shown = 1;

		if (!graph_is_commit_finished(graph))
			putchar('\n');
		else
			break;
	}
	strbuf_release(&msgbuf);

	return shown;
}