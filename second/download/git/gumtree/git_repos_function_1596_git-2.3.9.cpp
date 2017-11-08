static int open_packed_git_1(struct packed_git *p)
{
	struct stat st;
	struct pack_header hdr;
	unsigned char sha1[20];
	unsigned char *idx_sha1;
	long fd_flag;

	if (!p->index_data && open_pack_index(p))
		return error("packfile %s index unavailable", p->pack_name);

	if (!pack_max_fds) {
		unsigned int max_fds = get_max_fd_limit();

		/* Save 3 for stdin/stdout/stderr, 22 for work */
		if (25 < max_fds)
			pack_max_fds = max_fds - 25;
		else
			pack_max_fds = 1;
	}

	while (pack_max_fds <= pack_open_fds && close_one_pack())
		; /* nothing */

	p->pack_fd = git_open_noatime(p->pack_name);
	if (p->pack_fd < 0 || fstat(p->pack_fd, &st))
		return -1;
	pack_open_fds++;

	/* If we created the struct before we had the pack we lack size. */
	if (!p->pack_size) {
		if (!S_ISREG(st.st_mode))
			return error("packfile %s not a regular file", p->pack_name);
		p->pack_size = st.st_size;
	} else if (p->pack_size != st.st_size)
		return error("packfile %s size changed", p->pack_name);

	/* We leave these file descriptors open with sliding mmap;
	 * there is no point keeping them open across exec(), though.
	 */
	fd_flag = fcntl(p->pack_fd, F_GETFD, 0);
	if (fd_flag < 0)
		return error("cannot determine file descriptor flags");
	fd_flag |= FD_CLOEXEC;
	if (fcntl(p->pack_fd, F_SETFD, fd_flag) == -1)
		return error("cannot set FD_CLOEXEC");

	/* Verify we recognize this pack file format. */
	if (read_in_full(p->pack_fd, &hdr, sizeof(hdr)) != sizeof(hdr))
		return error("file %s is far too short to be a packfile", p->pack_name);
	if (hdr.hdr_signature != htonl(PACK_SIGNATURE))
		return error("file %s is not a GIT packfile", p->pack_name);
	if (!pack_version_ok(hdr.hdr_version))
		return error("packfile %s is version %"PRIu32" and not"
			" supported (try upgrading GIT to a newer version)",
			p->pack_name, ntohl(hdr.hdr_version));

	/* Verify the pack matches its index. */
	if (p->num_objects != ntohl(hdr.hdr_entries))
		return error("packfile %s claims to have %"PRIu32" objects"
			     " while index indicates %"PRIu32" objects",
			     p->pack_name, ntohl(hdr.hdr_entries),
			     p->num_objects);
	if (lseek(p->pack_fd, p->pack_size - sizeof(sha1), SEEK_SET) == -1)
		return error("end of packfile %s is unavailable", p->pack_name);
	if (read_in_full(p->pack_fd, sha1, sizeof(sha1)) != sizeof(sha1))
		return error("packfile %s signature is unavailable", p->pack_name);
	idx_sha1 = ((unsigned char *)p->index_data) + p->index_size - 40;
	if (hashcmp(sha1, idx_sha1))
		return error("packfile %s does not match index", p->pack_name);
	return 0;
}