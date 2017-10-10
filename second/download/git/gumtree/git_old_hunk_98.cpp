			handle_commit(commit, &revs);
			handle_tail(&commits, &revs);
		}
	}

	handle_tags_and_duplicates();

	if (export_filename && lastimportid != last_idnum)
		export_marks(export_filename);

	if (use_done_feature)
		printf("done\n");

	return 0;
}
