static void find_move_in_parent(struct blame_scoreboard *sb,
				struct blame_entry ***blamed,
				struct blame_entry **toosmall,
				struct blame_origin *target,
				struct blame_origin *parent)
{
	struct blame_entry *e, split[3];
	struct blame_entry *unblamed = target->suspects;
	struct blame_entry *leftover = NULL;
	mmfile_t file_p;

	if (!unblamed)
		return; /* nothing remains for this target */

	fill_origin_blob(&sb->revs->diffopt, parent, &file_p, &sb->num_read_blob);
	if (!file_p.ptr)
		return;

	/* At each iteration, unblamed has a NULL-terminated list of
	 * entries that have not yet been tested for blame.  leftover
	 * contains the reversed list of entries that have been tested
	 * without being assignable to the parent.
	 */
	do {
		struct blame_entry **unblamedtail = &unblamed;
		struct blame_entry *next;
		for (e = unblamed; e; e = next) {
			next = e->next;
			find_copy_in_blob(sb, e, parent, split, &file_p);
			if (split[1].suspect &&
			    sb->move_score < blame_entry_score(sb, &split[1])) {
				split_blame(blamed, &unblamedtail, split, e);
			} else {
				e->next = leftover;
				leftover = e;
			}
			decref_split(split);
		}
		*unblamedtail = NULL;
		toosmall = filter_small(sb, toosmall, &unblamed, sb->move_score);
	} while (unblamed);
	target->suspects = reverse_blame(leftover, NULL);
}