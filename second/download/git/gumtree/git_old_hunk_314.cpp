}

/**
 * Clean the index without touching entries that are not modified between
 * `head` and `remote`.
 */
static int clean_index(const unsigned char *head, const unsigned char *remote)
{
	struct tree *head_tree, *remote_tree, *index_tree;
	unsigned char index[GIT_SHA1_RAWSZ];

	head_tree = parse_tree_indirect(head);
	if (!head_tree)
		return error(_("Could not parse object '%s'."), sha1_to_hex(head));

	remote_tree = parse_tree_indirect(remote);
	if (!remote_tree)
		return error(_("Could not parse object '%s'."), sha1_to_hex(remote));

	read_cache_unmerged();

	if (fast_forward_to(head_tree, head_tree, 1))
		return -1;

	if (write_cache_as_tree(index, 0, NULL))
		return -1;

	index_tree = parse_tree_indirect(index);
	if (!index_tree)
		return error(_("Could not parse object '%s'."), sha1_to_hex(index));

	if (fast_forward_to(index_tree, remote_tree, 0))
		return -1;

	if (merge_tree(remote_tree))
		return -1;
