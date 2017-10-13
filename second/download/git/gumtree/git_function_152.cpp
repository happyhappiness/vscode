int read_index_from(struct index_state *istate, const char *path)
{
	int fd, i;
	struct stat st;
	unsigned long src_offset;
	struct cache_header *hdr;
	void *mmap;
	size_t mmap_size;
	struct strbuf previous_name_buf = STRBUF_INIT, *previous_name;

	if (istate->initialized)
		return istate->cache_nr;

	istate->timestamp.sec = 0;
	istate->timestamp.nsec = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0) {
		if (errno == ENOENT)
			return 0;
		die_errno("index file open failed");
	}

	if (fstat(fd, &st))
		die_errno("cannot stat the open index");

	mmap_size = xsize_t(st.st_size);
	if (mmap_size < sizeof(struct cache_header) + 20)
		die("index file smaller than expected");

	mmap = xmmap(NULL, mmap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (mmap == MAP_FAILED)
		die_errno("unable to map index file");
	close(fd);

	hdr = mmap;
	if (verify_hdr(hdr, mmap_size) < 0)
		goto unmap;

	hashcpy(istate->sha1, (unsigned char *)hdr + mmap_size - 20);
	istate->version = ntohl(hdr->hdr_version);
	istate->cache_nr = ntohl(hdr->hdr_entries);
	istate->cache_alloc = alloc_nr(istate->cache_nr);
	istate->cache = xcalloc(istate->cache_alloc, sizeof(*istate->cache));
	istate->initialized = 1;

	if (istate->version == 4)
		previous_name = &previous_name_buf;
	else
		previous_name = NULL;

	src_offset = sizeof(*hdr);
	for (i = 0; i < istate->cache_nr; i++) {
		struct ondisk_cache_entry *disk_ce;
		struct cache_entry *ce;
		unsigned long consumed;

		disk_ce = (struct ondisk_cache_entry *)((char *)mmap + src_offset);
		ce = create_from_disk(disk_ce, &consumed, previous_name);
		set_index_entry(istate, i, ce);

		src_offset += consumed;
	}
	strbuf_release(&previous_name_buf);
	istate->timestamp.sec = st.st_mtime;
	istate->timestamp.nsec = ST_MTIME_NSEC(st);

	while (src_offset <= mmap_size - 20 - 8) {
		/* After an array of active_nr index entries,
		 * there can be arbitrary number of extended
		 * sections, each of which is prefixed with
		 * extension name (4-byte) and section length
		 * in 4-byte network byte order.
		 */
		uint32_t extsize;
		memcpy(&extsize, (char *)mmap + src_offset + 4, 4);
		extsize = ntohl(extsize);
		if (read_index_extension(istate,
					 (const char *) mmap + src_offset,
					 (char *) mmap + src_offset + 8,
					 extsize) < 0)
			goto unmap;
		src_offset += 8;
		src_offset += extsize;
	}
	munmap(mmap, mmap_size);
	return istate->cache_nr;

unmap:
	munmap(mmap, mmap_size);
	die("index file corrupt");
}