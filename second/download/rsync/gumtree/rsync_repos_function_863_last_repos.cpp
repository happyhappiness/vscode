ssize_t sys_lgetxattr(const char *path, const char *name, void *value, size_t size)
{
	ssize_t len = getxattr(path, name, value, size, 0, XATTR_NOFOLLOW);

	/* If we're retrieving data, handle resource forks > 64MB specially */
	if (value != NULL && len == GETXATTR_FETCH_LIMIT && (size_t)len < size) {
		/* getxattr will only return 64MB of data at a time, need to call again with a new offset */
		u_int32_t offset = len;
		size_t data_retrieved = len;
		while (data_retrieved < size) {
			len = getxattr(path, name, value + offset, size - data_retrieved, offset, XATTR_NOFOLLOW);
			if (len <= 0)
				break;
			data_retrieved += len;
			offset += (u_int32_t)len;
		}
		len = data_retrieved;
	}

	return len;
}