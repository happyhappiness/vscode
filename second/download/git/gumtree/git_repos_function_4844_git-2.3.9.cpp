static int add_existing(const char *refname, const unsigned char *sha1,
			int flag, void *cbdata)
{
	struct string_list *list = (struct string_list *)cbdata;
	struct string_list_item *item = string_list_insert(list, refname);
	item->util = xmalloc(20);
	hashcpy(item->util, sha1);
	return 0;
}