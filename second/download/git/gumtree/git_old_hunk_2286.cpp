			commit_list_insert(commit, &complete);
		}
	}
	return 0;
}

static void mark_recent_complete_commits(struct fetch_pack_args *args,
					 unsigned long cutoff)
{
	while (complete && cutoff <= complete->item->date) {
		if (args->verbose)
			fprintf(stderr, "Marking %s as complete\n",
