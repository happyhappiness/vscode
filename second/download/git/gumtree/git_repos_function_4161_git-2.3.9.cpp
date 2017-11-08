static void report_tracking(struct branch_info *new)
{
	struct strbuf sb = STRBUF_INIT;
	struct branch *branch = branch_get(new->name);

	if (!format_tracking_info(branch, &sb))
		return;
	fputs(sb.buf, stdout);
	strbuf_release(&sb);
}