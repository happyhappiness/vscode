static void *lock_and_read_sha1_file(const unsigned char *sha1, enum object_type *type, unsigned long *size)
{
	void *data;

	grep_read_lock();
	data = read_sha1_file(sha1, type, size);
	grep_read_unlock();
	return data;
}