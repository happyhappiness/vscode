static struct blame_origin *get_origin(struct commit *commit, const char *path)
{
	struct blame_origin *o, *l;

	for (o = commit->util, l = NULL; o; l = o, o = o->next) {
		if (!strcmp(o->path, path)) {
			/* bump to front */
			if (l) {
				l->next = o->next;
				o->next = commit->util;
				commit->util = o;
			}
			return blame_origin_incref(o);
		}
	}
	return make_origin(commit, path);
}