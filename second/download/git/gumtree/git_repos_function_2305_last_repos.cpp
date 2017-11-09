static int index_stream(unsigned char *sha1, int fd, size_t size,
			enum object_type type, const char *path,
			unsigned flags)
{
	return index_bulk_checkin(sha1, fd, size, type, path, flags);
}