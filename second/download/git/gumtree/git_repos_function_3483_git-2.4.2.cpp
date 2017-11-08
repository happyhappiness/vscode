static void add_to_tips(struct tips *tips, const unsigned char *sha1)
{
	struct commit *commit;

	if (is_null_sha1(sha1))
		return;
	commit = lookup_commit_reference_gently(sha1, 1);
	if (!commit || (commit->object.flags & TMP_MARK))
		return;
	commit->object.flags |= TMP_MARK;
	ALLOC_GROW(tips->tip, tips->nr + 1, tips->alloc);
	tips->tip[tips->nr++] = commit;
}