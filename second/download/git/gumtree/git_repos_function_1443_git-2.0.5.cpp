static int fsck_commit_buffer(struct commit *commit, const char *buffer,
			      fsck_error error_func)
{
	const char *tmp;
	unsigned char tree_sha1[20], sha1[20];
	struct commit_graft *graft;
	int parents = 0;
	int err;

	buffer = skip_prefix(buffer, "tree ");
	if (!buffer)
		return error_func(&commit->object, FSCK_ERROR, "invalid format - expected 'tree' line");
	if (get_sha1_hex(buffer, tree_sha1) || buffer[40] != '\n')
		return error_func(&commit->object, FSCK_ERROR, "invalid 'tree' line format - bad sha1");
	buffer += 41;
	while ((tmp = skip_prefix(buffer, "parent "))) {
		buffer = tmp;
		if (get_sha1_hex(buffer, sha1) || buffer[40] != '\n')
			return error_func(&commit->object, FSCK_ERROR, "invalid 'parent' line format - bad sha1");
		buffer += 41;
		parents++;
	}
	graft = lookup_commit_graft(commit->object.sha1);
	if (graft) {
		struct commit_list *p = commit->parents;
		parents = 0;
		while (p) {
			p = p->next;
			parents++;
		}
		if (graft->nr_parent == -1 && !parents)
			; /* shallow commit */
		else if (graft->nr_parent != parents)
			return error_func(&commit->object, FSCK_ERROR, "graft objects missing");
	} else {
		struct commit_list *p = commit->parents;
		while (p && parents) {
			p = p->next;
			parents--;
		}
		if (p || parents)
			return error_func(&commit->object, FSCK_ERROR, "parent objects missing");
	}
	buffer = skip_prefix(buffer, "author ");
	if (!buffer)
		return error_func(&commit->object, FSCK_ERROR, "invalid format - expected 'author' line");
	err = fsck_ident(&buffer, &commit->object, error_func);
	if (err)
		return err;
	buffer = skip_prefix(buffer, "committer ");
	if (!buffer)
		return error_func(&commit->object, FSCK_ERROR, "invalid format - expected 'committer' line");
	err = fsck_ident(&buffer, &commit->object, error_func);
	if (err)
		return err;
	if (!commit->tree)
		return error_func(&commit->object, FSCK_ERROR, "could not load commit's tree %s", sha1_to_hex(tree_sha1));

	return 0;
}