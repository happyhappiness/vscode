			if (revs->max_age != -1 &&
			    (commit->date < revs->max_age))
				continue;
			if (add_parents_to_list(revs, commit, &revs->commits, NULL) < 0) {
				if (!revs->ignore_missing_links)
					die("Failed to traverse parents of commit %s",
						sha1_to_hex(commit->object.sha1));
			}
		}

		switch (simplify_commit(revs, commit)) {
		case commit_ignore:
			continue;
		case commit_error:
			die("Failed to simplify parents of commit %s",
			    sha1_to_hex(commit->object.sha1));
		default:
			if (revs->track_linear)
				track_linear(revs, commit);
			return commit;
		}
	} while (revs->commits);
