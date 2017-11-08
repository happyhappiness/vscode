int commit_patch_id(struct commit *commit, struct diff_options *options,
		    struct object_id *oid, int diff_header_only)
{
	if (!patch_id_defined(commit))
		return -1;

	if (commit->parents)
		diff_tree_oid(&commit->parents->item->object.oid,
			      &commit->object.oid, "", options);
	else
		diff_root_tree_oid(&commit->object.oid, "", options);
	diffcore_std(options);
	return diff_flush_patch_id(options, oid, diff_header_only);
}