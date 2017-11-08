static inline int is_loose_object_file(struct dirent *de,
				       char *name, unsigned char *sha1)
{
	if (strlen(de->d_name) != 38)
		return 0;
	memcpy(name + 2, de->d_name, 39);
	return !get_sha1_hex(name, sha1);
}