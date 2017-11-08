static void *read_object(const unsigned char *sha1, enum object_type *type,
			 unsigned long *size)
{
	unsigned long mapsize;
	void *map, *buf;
	struct cached_object *co;

	co = find_cached_object(sha1);
	if (co) {
		*type = co->type;
		*size = co->size;
		return xmemdupz(co->buf, co->size);
	}

	buf = read_packed_sha1(sha1, type, size);
	if (buf)
		return buf;
	map = map_sha1_file(sha1, &mapsize);
	if (map) {
		buf = unpack_sha1_file(map, mapsize, type, size, sha1);
		munmap(map, mapsize);
		return buf;
	}
	reprepare_packed_git();
	return read_packed_sha1(sha1, type, size);
}