int has_object_file(const struct object_id *oid)
{
	return has_sha1_file(oid->hash);
}