static void split_blame(struct scoreboard *sb,
			struct blame_entry *split,
			struct blame_entry *e)
{
	struct blame_entry *new_entry;

	if (split[0].suspect && split[2].suspect) {
		/* The first part (reuse storage for the existing entry e) */
		dup_entry(e, &split[0]);

		/* The last part -- me */
		new_entry = xmalloc(sizeof(*new_entry));
		memcpy(new_entry, &(split[2]), sizeof(struct blame_entry));
		add_blame_entry(sb, new_entry);

		/* ... and the middle part -- parent */
		new_entry = xmalloc(sizeof(*new_entry));
		memcpy(new_entry, &(split[1]), sizeof(struct blame_entry));
		add_blame_entry(sb, new_entry);
	}
	else if (!split[0].suspect && !split[2].suspect)
		/*
		 * The parent covers the entire area; reuse storage for
		 * e and replace it with the parent.
		 */
		dup_entry(e, &split[1]);
	else if (split[0].suspect) {
		/* me and then parent */
		dup_entry(e, &split[0]);

		new_entry = xmalloc(sizeof(*new_entry));
		memcpy(new_entry, &(split[1]), sizeof(struct blame_entry));
		add_blame_entry(sb, new_entry);
	}
	else {
		/* parent and then me */
		dup_entry(e, &split[1]);

		new_entry = xmalloc(sizeof(*new_entry));
		memcpy(new_entry, &(split[2]), sizeof(struct blame_entry));
		add_blame_entry(sb, new_entry);
	}

	if (DEBUG) { /* sanity */
		struct blame_entry *ent;
		int lno = sb->ent->lno, corrupt = 0;

		for (ent = sb->ent; ent; ent = ent->next) {
			if (lno != ent->lno)
				corrupt = 1;
			if (ent->s_lno < 0)
				corrupt = 1;
			lno += ent->num_lines;
		}
		if (corrupt) {
			lno = sb->ent->lno;
			for (ent = sb->ent; ent; ent = ent->next) {
				printf("L %8d l %8d n %8d\n",
				       lno, ent->lno, ent->num_lines);
				lno = ent->lno + ent->num_lines;
			}
			die("oops");
		}
	}
}