static void mark_recent_complete_commits(struct fetch_pack_args *args,
					 unsigned long cutoff)
{
	while (complete && cutoff <= complete->item->date) {
		if (args->verbose)
			fprintf(stderr, "Marking %s as complete\n",
				sha1_to_hex(complete->item->object.sha1));
		pop_most_recent_commit(&complete, COMPLETE);
	}
}