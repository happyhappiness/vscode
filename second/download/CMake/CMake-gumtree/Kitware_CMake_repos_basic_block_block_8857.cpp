{
	struct archive_match *a;

	if (_a == NULL)
		return (ARCHIVE_OK);
	archive_check_magic(_a, ARCHIVE_MATCH_MAGIC,
	    ARCHIVE_STATE_ANY | ARCHIVE_STATE_FATAL, "archive_match_free");
	a = (struct archive_match *)_a;
	match_list_free(&(a->inclusions));
	match_list_free(&(a->exclusions));
	entry_list_free(&(a->exclusion_entry_list));
	free(a->inclusion_uids.ids);
	free(a->inclusion_gids.ids);
	match_list_free(&(a->inclusion_unames));
	match_list_free(&(a->inclusion_gnames));
	free(a);
	return (ARCHIVE_OK);
}