				oid_to_hex(&gave_up_on->object.oid));
		}
	}

	display_name(all_matches[0].name);
	if (abbrev)
		show_suffix(all_matches[0].depth, cmit->object.oid.hash);
	if (dirty)
		printf("%s", dirty);
	printf("\n");

	if (!last_one)
		clear_commit_marks(cmit, -1);
}

