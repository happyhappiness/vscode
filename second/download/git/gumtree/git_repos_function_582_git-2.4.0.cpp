int index_bulk_checkin(unsigned char *sha1,
		       int fd, size_t size, enum object_type type,
		       const char *path, unsigned flags)
{
	int status = deflate_to_pack(&state, sha1, fd, size, type,
				     path, flags);
	if (!state.plugged)
		finish_bulk_checkin(&state);
	return status;
}