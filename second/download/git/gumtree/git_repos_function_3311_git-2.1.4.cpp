static struct ref *alloc_delete_ref(void)
{
	struct ref *ref = alloc_ref("(delete)");
	hashclr(ref->new_sha1);
	return ref;
}