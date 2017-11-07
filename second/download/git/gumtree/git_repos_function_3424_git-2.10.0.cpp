int commit_patch_id(struct commit *commit, struct diff_options *options,
		    unsigned char *sha1, int diff_header_only)
{
	if (commit->parents)
		diff_tree_sha1(commit->parents->item->object.oid.hash,
			       commit->object.oid.hash, "", options);
	else
		diff_root_tree_sha1(commit->object.oid.hash, "", options);
	diffcore_std(options);
	return diff_flush_patch_id(options, sha1, diff_header_only);
}