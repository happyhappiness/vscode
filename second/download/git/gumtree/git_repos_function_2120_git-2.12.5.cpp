int has_object_file_with_flags(const struct object_id *oid, int flags)
{
	return has_sha1_file_with_flags(oid->hash, flags);
}