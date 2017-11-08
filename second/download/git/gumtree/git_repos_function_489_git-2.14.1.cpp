static void copy_split_if_better(struct blame_scoreboard *sb,
				 struct blame_entry *best_so_far,
				 struct blame_entry *this)
{
	int i;

	if (!this[1].suspect)
		return;
	if (best_so_far[1].suspect) {
		if (blame_entry_score(sb, &this[1]) < blame_entry_score(sb, &best_so_far[1]))
			return;
	}

	for (i = 0; i < 3; i++)
		blame_origin_incref(this[i].suspect);
	decref_split(best_so_far);
	memcpy(best_so_far, this, sizeof(struct blame_entry [3]));
}