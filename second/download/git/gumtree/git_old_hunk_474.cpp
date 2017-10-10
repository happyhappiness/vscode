}

static void mark_recent_complete_commits(struct fetch_pack_args *args,
					 unsigned long cutoff)
{
	while (complete && cutoff <= complete->item->date) {
		if (args->verbose)
			fprintf(stderr, "Marking %s as complete\n",
				oid_to_hex(&complete->item->object.oid));
		pop_most_recent_commit(&complete, COMPLETE);
	}
}

static void filter_refs(struct fetch_pack_args *args,
			struct ref **refs,
