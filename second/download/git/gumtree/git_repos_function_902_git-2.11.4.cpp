static inline int is_null_oid(const struct object_id *oid)
{
	return !hashcmp(oid->hash, null_sha1);
}