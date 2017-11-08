static void split_blame(struct blame_entry ***blamed,
			struct blame_entry ***unblamed,
			struct blame_entry *split,
			struct blame_entry *e)
{
	if (split[0].suspect && split[2].suspect) {
		/* The first part (reuse storage for the existing entry e) */
		dup_entry(unblamed, e, &split[0]);

		/* The last part -- me */
		add_blame_entry(unblamed, &split[2]);

		/* ... and the middle part -- parent */
		add_blame_entry(blamed, &split[1]);
	}
	else if (!split[0].suspect && !split[2].suspect)
		/*
		 * The parent covers the entire area; reuse storage for
		 * e and replace it with the parent.
		 */
		dup_entry(blamed, e, &split[1]);
	else if (split[0].suspect) {
		/* me and then parent */
		dup_entry(unblamed, e, &split[0]);
		add_blame_entry(blamed, &split[1]);
	}
	else {
		/* parent and then me */
		dup_entry(blamed, e, &split[1]);
		add_blame_entry(unblamed, &split[2]);
	}
}