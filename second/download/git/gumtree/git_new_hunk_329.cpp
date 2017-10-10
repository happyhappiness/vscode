		setup_work_tree();
		sb.final = fake_working_tree_commit(&sb.revs->diffopt,
						    path, contents_from);
		add_pending_object(&revs, &(sb.final->object), ":");
	}
	else if (contents_from)
		die(_("cannot use --contents with final commit object name"));

	if (reverse && revs.first_parent_only) {
		final_commit = find_single_final(sb.revs, NULL);
		if (!final_commit)
			die(_("--reverse and --first-parent together require specified latest commit"));
	}

	/*
	 * If we have bottom, this will mark the ancestors of the
	 * bottom commits we would reach while traversing as
	 * uninteresting.
