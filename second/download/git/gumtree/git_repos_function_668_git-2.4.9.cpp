int commit_tree(const char *msg, size_t msg_len,
		const unsigned char *tree,
		struct commit_list *parents, unsigned char *ret,
		const char *author, const char *sign_commit)
{
	struct commit_extra_header *extra = NULL, **tail = &extra;
	int result;

	append_merge_tag_headers(parents, &tail);
	result = commit_tree_extended(msg, msg_len, tree, parents, ret,
				      author, sign_commit, extra);
	free_commit_extra_headers(extra);
	return result;
}