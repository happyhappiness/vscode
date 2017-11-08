static void pass_whole_blame(struct scoreboard *sb,
			     struct origin *origin, struct origin *porigin)
{
	struct blame_entry *e, *suspects;

	if (!porigin->file.ptr && origin->file.ptr) {
		/* Steal its file */
		porigin->file = origin->file;
		origin->file.ptr = NULL;
	}
	suspects = origin->suspects;
	origin->suspects = NULL;
	for (e = suspects; e; e = e->next) {
		origin_incref(porigin);
		origin_decref(e->suspect);
		e->suspect = porigin;
	}
	queue_blames(sb, porigin, suspects);
}