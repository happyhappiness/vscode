static struct origin *make_origin(struct commit *commit, const char *path)
{
	struct origin *o;
	FLEX_ALLOC_STR(o, path, path);
	o->commit = commit;
	o->refcnt = 1;
	o->next = commit->util;
	commit->util = o;
	return o;
}