static int check_packed_git_idx(const char *path, struct packed_git *p)
{
	void *idx_map;
	struct pack_idx_header *hdr;
	size_t idx_size;
	uint32_t version, nr, i, *index;
	int fd = git_open_noatime(path);
	struct stat st;

	if (fd < 0)
		return -1;
	if (fstat(fd, &st)) {
		close(fd);
		return -1;
	}
	idx_size = xsize_t(st.st_size);
	if (idx_size < 4 * 256 + 20 + 20) {
		close(fd);
		return error("index file %s is too small", path);
	}
	idx_map = xmmap(NULL, idx_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);

	hdr = idx_map;
	if (hdr->idx_signature == htonl(PACK_IDX_SIGNATURE)) {
		version = ntohl(hdr->idx_version);
		if (version < 2 || version > 2) {
			munmap(idx_map, idx_size);
			return error("index file %s is version %"PRIu32
				     " and is not supported by this binary"
				     " (try upgrading GIT to a newer version)",
				     path, version);
		}
	} else
		version = 1;

	nr = 0;
	index = idx_map;
	if (version > 1)
		index += 2;  /* skip index header */
	for (i = 0; i < 256; i++) {
		uint32_t n = ntohl(index[i]);
		if (n < nr) {
			munmap(idx_map, idx_size);
			return error("non-monotonic index %s", path);
		}
		nr = n;
	}

	if (version == 1) {
		/*
		 * Total size:
		 *  - 256 index entries 4 bytes each
		 *  - 24-byte entries * nr (20-byte sha1 + 4-byte offset)
		 *  - 20-byte SHA1 of the packfile
		 *  - 20-byte SHA1 file checksum
		 */
		if (idx_size != 4*256 + nr * 24 + 20 + 20) {
			munmap(idx_map, idx_size);
			return error("wrong index v1 file size in %s", path);
		}
	} else if (version == 2) {
		/*
		 * Minimum size:
		 *  - 8 bytes of header
		 *  - 256 index entries 4 bytes each
		 *  - 20-byte sha1 entry * nr
		 *  - 4-byte crc entry * nr
		 *  - 4-byte offset entry * nr
		 *  - 20-byte SHA1 of the packfile
		 *  - 20-byte SHA1 file checksum
		 * And after the 4-byte offset table might be a
		 * variable sized table containing 8-byte entries
		 * for offsets larger than 2^31.
		 */
		unsigned long min_size = 8 + 4*256 + nr*(20 + 4 + 4) + 20 + 20;
		unsigned long max_size = min_size;
		if (nr)
			max_size += (nr - 1)*8;
		if (idx_size < min_size || idx_size > max_size) {
			munmap(idx_map, idx_size);
			return error("wrong index v2 file size in %s", path);
		}
		if (idx_size != min_size &&
		    /*
		     * make sure we can deal with large pack offsets.
		     * 31-bit signed offset won't be enough, neither
		     * 32-bit unsigned one will be.
		     */
		    (sizeof(off_t) <= 4)) {
			munmap(idx_map, idx_size);
			return error("pack too large for current definition of off_t in %s", path);
		}
	}

	p->index_version = version;
	p->index_data = idx_map;
	p->index_size = idx_size;
	p->num_objects = nr;
	return 0;
}