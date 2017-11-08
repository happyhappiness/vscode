static void split_blame(struct blame_entry ***blamed,
			struct blame_entry ***unblamed,
			struct blame_entry *split,
			struct blame_entry *e)
{
	struct blame_entry *new_entry;

	if (split[0].suspect && split[2].suspect) {
		/* The first part (reuse storage for the existing entry e) */
		dup_entry(unblamed, e, &split[0]);

		/* The last part -- me */
		new_entry = xmalloc(sizeof(*new_entry));
		memcpy(new_entry, &(split[2]), sizeof(struct blame_entry));
		add_blame_entry(unblamed, new_entry);

		/* ... and the middle part -- parent */
		new_entry = xmalloc(sizeof(*new_entry));
		memcpy(new_entry, &(split[1]), sizeof(struct blame_entry));
		add_blame_entry(blamed, new_entry);
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

		new_entry = xmalloc(sizeof(*new_entry));
		memcpy(new_entry, &(split[1]), sizeof(struct blame_entry));
		add_blame_entry(blamed, new_entry);
	}
	else {
		/* parent and then me */
		dup_entry(blamed, e, &split[1]);

		new_entry = xmalloc(sizeof(*new_entry));
		memcpy(new_entry, &(split[2]), sizeof(struct blame_entry));
		add_blame_entry(unblamed, new_entry);
	}
}