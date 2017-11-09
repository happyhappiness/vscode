void rerere_clear(struct string_list *merge_rr)
{
	int i;

	if (setup_rerere(merge_rr, 0) < 0)
		return;

	for (i = 0; i < merge_rr->nr; i++) {
		struct rerere_id *id = merge_rr->items[i].util;
		if (!has_rerere_resolution(id)) {
			unlink_rr_item(id);
			rmdir(rerere_path(id, NULL));
		}
	}
	unlink_or_warn(git_path_merge_rr());
	rollback_lock_file(&write_lock);
}