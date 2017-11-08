static struct origin *make_origin(struct commit *commit, const char *path)
{
	struct origin *o;
	size_t pathlen = strlen(path) + 1;
	o = xcalloc(1, sizeof(*o) + pathlen);
	o->commit = commit;
	o->refcnt = 1;
	o->next = commit->util;
	commit->util = o;
	memcpy(o->path, path, pathlen); /* includes NUL */
	return o;
}