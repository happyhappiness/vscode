static struct ref_array_item *new_ref_array_item(const char *refname,
						 const unsigned char *objectname,
						 int flag)
{
	struct ref_array_item *ref;
	FLEX_ALLOC_STR(ref, refname, refname);
	hashcpy(ref->objectname.hash, objectname);
	ref->flag = flag;

	return ref;
}