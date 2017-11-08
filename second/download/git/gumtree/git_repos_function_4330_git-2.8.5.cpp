static struct origin *get_origin(struct scoreboard *sb,
				 struct commit *commit,
				 const char *path)
{
	struct origin *o, *l;

	for (o = commit->util, l = NULL; o; l = o, o = o->next) {
		if (!strcmp(o->path, path)) {
			/* bump to front */
			if (l) {
				l->next = o->next;
				o->next = commit->util;
				commit->util = o;
			}
			return origin_incref(o);
		}
	}
	return make_origin(commit, path);
}