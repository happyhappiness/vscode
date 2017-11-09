static int add_existing(const char *refname, const struct object_id *oid,
			int flag, void *cbdata)
{
	struct string_list *list = (struct string_list *)cbdata;
	struct string_list_item *item = string_list_insert(list, refname);
	struct object_id *old_oid = xmalloc(sizeof(*old_oid));

	oidcpy(old_oid, oid);
	item->util = old_oid;
	return 0;
}