int read_loose_object(const char *path,
		      const unsigned char *expected_sha1,
		      enum object_type *type,
		      unsigned long *size,
		      void **contents)
{
	int ret = -1;
	int fd = -1;
	void *map = NULL;
	unsigned long mapsize;
	git_zstream stream;
	char hdr[32];

	*contents = NULL;

	map = map_sha1_file_1(path, NULL, &mapsize);
	if (!map) {
		error_errno("unable to mmap %s", path);
		goto out;
	}

	if (unpack_sha1_header(&stream, map, mapsize, hdr, sizeof(hdr)) < 0) {
		error("unable to unpack header of %s", path);
		goto out;
	}

	*type = parse_sha1_header(hdr, size);
	if (*type < 0) {
		error("unable to parse header of %s", path);
		git_inflate_end(&stream);
		goto out;
	}

	if (*type == OBJ_BLOB) {
		if (check_stream_sha1(&stream, hdr, *size, path, expected_sha1) < 0)
			goto out;
	} else {
		*contents = unpack_sha1_rest(&stream, hdr, *size, expected_sha1);
		if (!*contents) {
			error("unable to unpack contents of %s", path);
			git_inflate_end(&stream);
			goto out;
		}
		if (check_sha1_signature(expected_sha1, *contents,
					 *size, typename(*type))) {
			error("sha1 mismatch for %s (expected %s)", path,
			      sha1_to_hex(expected_sha1));
			free(*contents);
			goto out;
		}
	}

	ret = 0; /* everything checks out */

out:
	if (map)
		munmap(map, mapsize);
	if (fd >= 0)
		close(fd);
	return ret;
}