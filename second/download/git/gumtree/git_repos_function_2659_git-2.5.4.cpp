static int resolve_gitlink_packed_ref(struct ref_cache *refs,
				      const char *refname, unsigned char *sha1)
{
	struct ref_entry *ref;
	struct ref_dir *dir = get_packed_refs(refs);

	ref = find_ref(dir, refname);
	if (ref == NULL)
		return -1;

	hashcpy(sha1, ref->u.value.oid.hash);
	return 0;
}