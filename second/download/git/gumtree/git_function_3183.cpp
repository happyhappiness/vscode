void print_commit_list(struct commit_list *list,
		       const char *format_cur,
		       const char *format_last)
{
	for ( ; list; list = list->next) {
		const char *format = list->next ? format_cur : format_last;
		printf(format, oid_to_hex(&list->item->object.oid));
	}
}