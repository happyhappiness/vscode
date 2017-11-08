static int commit_patch_id(struct commit *commit, struct diff_options *options,
		    unsigned char *sha1)
{
	if (commit->parents)
		diff_tree_sha1(commit->parents->item->object.sha1,
		               commit->object.sha1, "", options);
	else
		diff_root_tree_sha1(commit->object.sha1, "", options);
	diffcore_std(options);
	return diff_flush_patch_id(options, sha1);
}