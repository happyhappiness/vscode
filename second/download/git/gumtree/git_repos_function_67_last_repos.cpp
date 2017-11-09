static int cmd_group_cmp(const void *elem1, const void *elem2)
{
	const struct cmdname_help *e1 = elem1;
	const struct cmdname_help *e2 = elem2;

	if (e1->group < e2->group)
		return -1;
	if (e1->group > e2->group)
		return 1;
	return strcmp(e1->name, e2->name);
}