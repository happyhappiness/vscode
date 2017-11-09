void blame_coalesce(struct blame_scoreboard *sb)
{
	struct blame_entry *ent, *next;

	for (ent = sb->ent; ent && (next = ent->next); ent = next) {
		if (ent->suspect == next->suspect &&
		    ent->s_lno + ent->num_lines == next->s_lno) {
			ent->num_lines += next->num_lines;
			ent->next = next->next;
			blame_origin_decref(next->suspect);
			free(next);
			ent->score = 0;
			next = ent; /* again */
		}
	}

	if (sb->debug) /* sanity */
		sanity_check_refcnt(sb);
}