static struct oid_array *submodule_commits(struct string_list *submodules,
					   const char *path)
{
	struct string_list_item *item;

	item = string_list_insert(submodules, path);
	if (item->util)
		return (struct oid_array *) item->util;

	/* NEEDSWORK: should we have oid_array_init()? */
	item->util = xcalloc(1, sizeof(struct oid_array));
	return (struct oid_array *) item->util;
}