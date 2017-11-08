static void *unpack_sha1_file(void *map, unsigned long mapsize, enum object_type *type, unsigned long *size, const unsigned char *sha1)
{
	int ret;
	git_zstream stream;
	char hdr[8192];

	ret = unpack_sha1_header(&stream, map, mapsize, hdr, sizeof(hdr));
	if (ret < Z_OK || (*type = parse_sha1_header(hdr, size)) < 0)
		return NULL;

	return unpack_sha1_rest(&stream, hdr, *size, sha1);
}