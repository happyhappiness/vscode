static inline int is_empty_tree_oid(const struct object_id *oid)
{
	return !hashcmp(oid->hash, EMPTY_TREE_SHA1_BIN);
}