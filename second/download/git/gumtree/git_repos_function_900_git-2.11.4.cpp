static inline int oidcmp(const struct object_id *oid1, const struct object_id *oid2)
{
	return hashcmp(oid1->hash, oid2->hash);
}