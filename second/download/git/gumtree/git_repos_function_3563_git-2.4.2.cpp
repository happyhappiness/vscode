static const char *merge_argument(struct commit *commit)
{
	if (commit)
		return sha1_to_hex(commit->object.sha1);
	else
		return EMPTY_TREE_SHA1_HEX;
}