static int loosened_object_can_be_discarded(const struct object_id *oid,
					    timestamp_t mtime)
{
	if (!unpack_unreachable_expiration)
		return 0;
	if (mtime > unpack_unreachable_expiration)
		return 0;
	if (oid_array_lookup(&recent_objects, oid) >= 0)
		return 0;
	return 1;
}