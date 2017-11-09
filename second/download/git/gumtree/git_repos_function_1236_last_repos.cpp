int ref_excluded(struct string_list *ref_excludes, const char *path)
{
	struct string_list_item *item;

	if (!ref_excludes)
		return 0;
	for_each_string_list_item(item, ref_excludes) {
		if (!wildmatch(item->string, path, 0))
			return 1;
	}
	return 0;
}