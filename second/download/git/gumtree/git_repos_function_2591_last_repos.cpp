static void handle_filter(struct mailinfo *mi, struct strbuf *line)
{
	switch (mi->filter_stage) {
	case 0:
		if (!handle_commit_msg(mi, line))
			break;
		mi->filter_stage++;
	case 1:
		handle_patch(mi, line);
		break;
	}
}