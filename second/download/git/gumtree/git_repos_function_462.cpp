static struct ref_array_item *new_ref_array_item(const char *refname,
						 const unsigned char *objectname,
						 int flag)
{
	size_t len = strlen(refname);
	struct ref_array_item *ref = xcalloc(1, sizeof(struct ref_array_item) + len + 1);
	memcpy(ref->refname, refname, len);
	ref->refname[len] = '\0';
	hashcpy(ref->objectname, objectname);
	ref->flag = flag;

	return ref;
}