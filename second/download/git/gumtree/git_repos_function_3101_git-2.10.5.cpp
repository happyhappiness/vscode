static void exit_if_skipped_commits(struct commit_list *tried,
				    const struct object_id *bad)
{
	if (!tried)
		return;

	printf("There are only 'skip'ped commits left to test.\n"
	       "The first %s commit could be any of:\n", term_bad);

	for ( ; tried; tried = tried->next)
		printf("%s\n", oid_to_hex(&tried->item->object.oid));

	if (bad)
		printf("%s\n", oid_to_hex(bad));
	printf(_("We cannot bisect more!\n"));
	exit(2);
}