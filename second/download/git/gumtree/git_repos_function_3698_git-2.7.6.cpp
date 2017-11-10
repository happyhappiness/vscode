static void add_to_tips(struct tips *tips, const struct object_id *oid)
{
	struct commit *commit;

	if (is_null_oid(oid))
		return;
	commit = lookup_commit_reference_gently(oid->hash, 1);
	if (!commit || (commit->object.flags & TMP_MARK))
		return;
	commit->object.flags |= TMP_MARK;
	ALLOC_GROW(tips->tip, tips->nr + 1, tips->alloc);
	tips->tip[tips->nr++] = commit;
}