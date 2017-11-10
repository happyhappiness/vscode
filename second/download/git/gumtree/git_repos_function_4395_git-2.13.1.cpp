static const char *merge_argument(struct commit *commit)
{
	if (commit)
		return oid_to_hex(&commit->object.oid);
	else
		return EMPTY_TREE_SHA1_HEX;
}