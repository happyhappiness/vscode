static int fsck_commit_buffer(struct commit *commit, const char *buffer,
	unsigned long size, fsck_error error_func)
{
	unsigned char tree_sha1[20], sha1[20];
	struct commit_graft *graft;
	unsigned parent_count, parent_line_count = 0;
	int err;

	if (require_end_of_header(buffer, size, &commit->object, error_func))
		return -1;

	if (!skip_prefix(buffer, "tree ", &buffer))
		return error_func(&commit->object, FSCK_ERROR, "invalid format - expected 'tree' line");
	if (get_sha1_hex(buffer, tree_sha1) || buffer[40] != '\n')
		return error_func(&commit->object, FSCK_ERROR, "invalid 'tree' line format - bad sha1");
	buffer += 41;
	while (skip_prefix(buffer, "parent ", &buffer)) {
		if (get_sha1_hex(buffer, sha1) || buffer[40] != '\n')
			return error_func(&commit->object, FSCK_ERROR, "invalid 'parent' line format - bad sha1");
		buffer += 41;
		parent_line_count++;
	}
	graft = lookup_commit_graft(commit->object.sha1);
	parent_count = commit_list_count(commit->parents);
	if (graft) {
		if (graft->nr_parent == -1 && !parent_count)
			; /* shallow commit */
		else if (graft->nr_parent != parent_count)
			return error_func(&commit->object, FSCK_ERROR, "graft objects missing");
	} else {
		if (parent_count != parent_line_count)
			return error_func(&commit->object, FSCK_ERROR, "parent objects missing");
	}
	if (!skip_prefix(buffer, "author ", &buffer))
		return error_func(&commit->object, FSCK_ERROR, "invalid format - expected 'author' line");
	err = fsck_ident(&buffer, &commit->object, error_func);
	if (err)
		return err;
	if (!skip_prefix(buffer, "committer ", &buffer))
		return error_func(&commit->object, FSCK_ERROR, "invalid format - expected 'committer' line");
	err = fsck_ident(&buffer, &commit->object, error_func);
	if (err)
		return err;
	if (!commit->tree)
		return error_func(&commit->object, FSCK_ERROR, "could not load commit's tree %s", sha1_to_hex(tree_sha1));

	return 0;
}