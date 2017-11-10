int get_oid_hex(const char *hex, struct object_id *oid)
{
	return get_sha1_hex(hex, oid->hash);
}