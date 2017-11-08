static inline int is_empty_blob_oid(const struct object_id *oid)
{
	return !hashcmp(oid->hash, EMPTY_BLOB_SHA1_BIN);
}