static int mark_uninteresting(const char *refname,
			      const unsigned char *sha1,
			      int flags, void *cb_data)
{
	struct commit *commit = lookup_commit_reference_gently(sha1, 1);
	if (!commit)
		return 0;
	commit->object.flags |= UNINTERESTING;
	mark_parents_uninteresting(commit);
	return 0;
}