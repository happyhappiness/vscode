{
	for ( ; list; list = list->next) {
		const char *format = list->next ? format_cur : format_last;
		printf(format, sha1_to_hex(list->item->object.sha1));
	}
}
