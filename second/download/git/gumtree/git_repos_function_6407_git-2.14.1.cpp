static int should_pack_ref(const char *refname,
			   const struct object_id *oid, unsigned int ref_flags,
			   unsigned int pack_flags)
{
	/* Do not pack per-worktree refs: */
	if (ref_type(refname) != REF_TYPE_NORMAL)
		return 0;

	/* Do not pack non-tags unless PACK_REFS_ALL is set: */
	if (!(pack_flags & PACK_REFS_ALL) && !starts_with(refname, "refs/tags/"))
		return 0;

	/* Do not pack symbolic refs: */
	if (ref_flags & REF_ISSYMREF)
		return 0;

	/* Do not pack broken refs: */
	if (!ref_resolves_to_object(refname, oid, ref_flags))
		return 0;

	return 1;
}