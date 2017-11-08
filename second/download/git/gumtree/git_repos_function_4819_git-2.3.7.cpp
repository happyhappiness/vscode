static void handle_filter(struct strbuf *line)
{
	static int filter = 0;

	/* filter tells us which part we left off on */
	switch (filter) {
	case 0:
		if (!handle_commit_msg(line))
			break;
		filter++;
	case 1:
		handle_patch(line);
		break;
	}
}