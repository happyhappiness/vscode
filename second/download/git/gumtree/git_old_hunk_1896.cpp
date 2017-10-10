			die("unable to parse commit %s", name);
		if (flags & UNINTERESTING) {
			mark_parents_uninteresting(commit);
			revs->limited = 1;
		}
		if (revs->show_source && !commit->util)
			commit->util = (void *) name;
		return commit;
	}

	/*
	 * Tree object? Either mark it uninteresting, or add it
	 * to the list of objects to look at later..
