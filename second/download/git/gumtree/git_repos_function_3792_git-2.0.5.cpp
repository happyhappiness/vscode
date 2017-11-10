static struct origin *get_origin(struct scoreboard *sb,
				 struct commit *commit,
				 const char *path)
{
	struct blame_entry *e;

	for (e = sb->ent; e; e = e->next) {
		if (e->suspect->commit == commit &&
		    !strcmp(e->suspect->path, path))
			return origin_incref(e->suspect);
	}
	return make_origin(commit, path);
}