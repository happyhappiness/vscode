const struct object_id *nth_packed_object_oid(struct object_id *oid,
					      struct packed_git *p,
					      uint32_t n)
{
	const unsigned char *hash = nth_packed_object_sha1(p, n);
	if (!hash)
		return NULL;
	hashcpy(oid->hash, hash);
	return oid;
}