static void mark_alternate_complete(const struct ref *ref, void *unused)
{
	mark_complete(NULL, ref->old_sha1, 0, NULL);
}