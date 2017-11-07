static void pass_whole_blame(struct scoreboard *sb,
			     struct origin *origin, struct origin *porigin)
{
	struct blame_entry *e;

	if (!porigin->file.ptr && origin->file.ptr) {
		/* Steal its file */
		porigin->file = origin->file;
		origin->file.ptr = NULL;
	}
	for (e = sb->ent; e; e = e->next) {
		if (e->suspect != origin)
			continue;
		origin_incref(porigin);
		origin_decref(e->suspect);
		e->suspect = porigin;
	}
}