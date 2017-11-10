static int fsck_loose(const unsigned char *sha1, const char *path, void *data)
{
	if (fsck_sha1(sha1))
		errors_found |= ERROR_OBJECT;
	return 0;
}