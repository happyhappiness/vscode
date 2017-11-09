char *oid_to_hex_r(char *buffer, const struct object_id *oid)
{
	return sha1_to_hex_r(buffer, oid->hash);
}