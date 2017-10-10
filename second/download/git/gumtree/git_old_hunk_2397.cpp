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
