int get_oid(const char *name, struct object_id *oid)
{
	return get_sha1(name, oid->hash);
}