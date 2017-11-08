static void copy_split_if_better(struct scoreboard *sb,
				 struct blame_entry *best_so_far,
				 struct blame_entry *this)
{
	int i;

	if (!this[1].suspect)
		return;
	if (best_so_far[1].suspect) {
		if (ent_score(sb, &this[1]) < ent_score(sb, &best_so_far[1]))
			return;
	}

	for (i = 0; i < 3; i++)
		origin_incref(this[i].suspect);
	decref_split(best_so_far);
	memcpy(best_so_far, this, sizeof(struct blame_entry [3]));
}