static struct origin *make_origin(struct commit *commit, const char *path)
{
	struct origin *o;
	o = xcalloc(1, sizeof(*o) + strlen(path) + 1);
	o->commit = commit;
	o->refcnt = 1;
	o->next = commit->util;
	commit->util = o;
	strcpy(o->path, path);
	return o;
}