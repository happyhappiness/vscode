static void advertise_shallow_grafts_buf(struct strbuf *sb)
{
	if (!is_repository_shallow())
		return;
	for_each_commit_graft(advertise_shallow_grafts_cb, sb);
}