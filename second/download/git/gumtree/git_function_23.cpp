static void origin_decref(struct origin *o)
{
	if (o && --o->refcnt <= 0) {
		struct origin *p, *l = NULL;
		if (o->previous)
			origin_decref(o->previous);
		free(o->file.ptr);
		/* Should be present exactly once in commit chain */
		for (p = o->commit->util; p; l = p, p = p->next) {
			if (p == o) {
				if (l)
					l->next = p->next;
				else
					o->commit->util = p->next;
				free(o);
				return;
			}
		}
		die("internal error in blame::origin_decref");
	}
}