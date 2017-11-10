static void mark_alternate_complete(const struct ref *ref, void *unused)
{
	mark_complete(ref->old_oid.hash);
}