static struct ref *alloc_delete_ref(void)
{
	struct ref *ref = alloc_ref("(delete)");
	oidclr(&ref->new_oid);
	return ref;
}