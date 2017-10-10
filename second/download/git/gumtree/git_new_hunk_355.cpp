		else
			die(_("No tags can describe '%s'.\n"
			    "Try --always, or create some tags."),
			    oid_to_hex(oid));
	}

	QSORT(all_matches, match_cnt, compare_pt);

	if (gave_up_on) {
		commit_list_insert_by_date(gave_up_on, &list);
		seen_commits--;
	}
	seen_commits += finish_depth_computation(&list, &all_matches[0]);
