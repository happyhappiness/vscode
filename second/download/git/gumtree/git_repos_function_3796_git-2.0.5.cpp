static void add_blame_entry(struct scoreboard *sb, struct blame_entry *e)
{
	struct blame_entry *ent, *prev = NULL;

	origin_incref(e->suspect);

	for (ent = sb->ent; ent && ent->lno < e->lno; ent = ent->next)
		prev = ent;

	/* prev, if not NULL, is the last one that is below e */

	if (prev) {
		e->next = prev->next;
		prev->next = e;
	}
	else {
		e->next = sb->ent;
		sb->ent = e;
	}
}