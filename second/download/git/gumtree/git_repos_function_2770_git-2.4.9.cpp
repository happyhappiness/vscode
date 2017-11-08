void rerere_clear(struct string_list *merge_rr)
{
	int i;

	for (i = 0; i < merge_rr->nr; i++) {
		const char *name = (const char *)merge_rr->items[i].util;
		if (!has_rerere_resolution(name))
			unlink_rr_item(name);
	}
	unlink_or_warn(git_path("MERGE_RR"));
}