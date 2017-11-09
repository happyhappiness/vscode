void *map_sha1_file(const unsigned char *sha1, unsigned long *size)
{
	return map_sha1_file_1(NULL, sha1, size);
}