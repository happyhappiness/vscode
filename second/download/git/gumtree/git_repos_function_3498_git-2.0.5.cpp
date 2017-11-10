static int string_list_add_one_ref(const char *refname, const unsigned char *sha1,
				   int flag, void *cb)
{
	struct string_list *refs = cb;
	if (!unsorted_string_list_has_string(refs, refname))
		string_list_append(refs, refname);
	return 0;
}