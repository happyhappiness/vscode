char *oid_to_hex(const struct object_id *oid)
{
	return sha1_to_hex(oid->hash);
}