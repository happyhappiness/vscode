ssize_t sys_llistxattr(const char *path, char *list, size_t size)
{
	unsigned char keylen;
	ssize_t off, len = extattr_list_link(path, EXTATTR_NAMESPACE_USER, list, size);

	if (len <= 0 || (size_t)len > size)
		return len;

	/* FreeBSD puts a single-byte length before each string, with no '\0'
	 * terminator.  We need to change this into a series of null-terminted
	 * strings.  Since the size is the same, we can simply transform the
	 * output in place. */
	for (off = 0; off < len; off += keylen + 1) {
		keylen = ((unsigned char*)list)[off];
		if (off + keylen >= len) {
			/* Should be impossible, but kernel bugs happen! */
			errno = EINVAL;
			return -1;
		}
		memmove(list+off, list+off+1, keylen);
		list[off+keylen] = '\0';
	}

	return len;
}