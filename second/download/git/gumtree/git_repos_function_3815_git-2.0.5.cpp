static void reset_scanned_flag(struct scoreboard *sb)
{
	struct blame_entry *e;
	for (e = sb->ent; e; e = e->next)
		e->scanned = 0;
}