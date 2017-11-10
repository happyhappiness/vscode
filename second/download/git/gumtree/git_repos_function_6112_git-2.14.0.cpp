static void *lock_and_read_oid_file(const struct object_id *oid, enum object_type *type, unsigned long *size)
{
	void *data;

	grep_read_lock();
	data = read_sha1_file(oid->hash, type, size);
	grep_read_unlock();
	return data;
}