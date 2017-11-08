static struct sha1_array *submodule_commits(struct string_list *submodules,
					    const char *path)
{
	struct string_list_item *item;

	item = string_list_insert(submodules, path);
	if (item->util)
		return (struct sha1_array *) item->util;

	/* NEEDSWORK: should we have sha1_array_init()? */
	item->util = xcalloc(1, sizeof(struct sha1_array));
	return (struct sha1_array *) item->util;
}