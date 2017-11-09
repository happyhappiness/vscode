static int add_existing(const char *refname, const struct object_id *oid,
			int flag, void *cbdata)
{
	struct string_list *list = (struct string_list *)cbdata;
	string_list_insert(list, refname);
	return 0;
}