static void coalesce(struct scoreboard *sb)
{
	struct blame_entry *ent, *next;

	for (ent = sb->ent; ent && (next = ent->next); ent = next) {
		if (ent->suspect == next->suspect &&
		    ent->s_lno + ent->num_lines == next->s_lno) {
			ent->num_lines += next->num_lines;
			ent->next = next->next;
			origin_decref(next->suspect);
			free(next);
			ent->score = 0;
			next = ent; /* again */
		}
	}

	if (DEBUG) /* sanity */
		sanity_check_refcnt(sb);
}