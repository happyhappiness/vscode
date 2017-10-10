static int is_original_commit_empty(struct commit *commit)
{
	const unsigned char *ptree_sha1;

	if (parse_commit(commit))
		return error(_("Could not parse commit %s\n"),
			     sha1_to_hex(commit->object.sha1));
	if (commit->parents) {
		struct commit *parent = commit->parents->item;
		if (parse_commit(parent))
			return error(_("Could not parse parent commit %s\n"),
				sha1_to_hex(parent->object.sha1));
		ptree_sha1 = parent->tree->object.sha1;
	} else {
		ptree_sha1 = EMPTY_TREE_SHA1_BIN; /* commit is root */
	}

	return !hashcmp(ptree_sha1, commit->tree->object.sha1);
}

/*
 * Do we run "git commit" with "--allow-empty"?
 */
static int allow_empty(struct replay_opts *opts, struct commit *commit)
