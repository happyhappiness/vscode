static int one_local_ref(const char *refname, const unsigned char *sha1, int flag, void *cb_data)
{
	struct ref ***local_tail = cb_data;
	struct ref *ref;
	int len;

	/* we already know it starts with refs/ to get here */
	if (check_refname_format(refname + 5, 0))
		return 0;

	len = strlen(refname) + 1;
	ref = xcalloc(1, sizeof(*ref) + len);
	hashcpy(ref->new_sha1, sha1);
	memcpy(ref->name, refname, len);
	**local_tail = ref;
	*local_tail = &ref->next;
	return 0;
}