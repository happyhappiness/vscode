int odb_pack_keep(char *name, size_t namesz, const unsigned char *sha1)
{
	int fd;

	snprintf(name, namesz, "%s/pack/pack-%s.keep",
		 get_object_directory(), sha1_to_hex(sha1));
	fd = open(name, O_RDWR|O_CREAT|O_EXCL, 0600);
	if (0 <= fd)
		return fd;

	/* slow path */
	safe_create_leading_directories(name);
	return open(name, O_RDWR|O_CREAT|O_EXCL, 0600);
}