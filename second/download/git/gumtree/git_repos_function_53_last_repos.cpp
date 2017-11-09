void fixup_pack_header_footer(int pack_fd,
			 unsigned char *new_pack_sha1,
			 const char *pack_name,
			 uint32_t object_count,
			 unsigned char *partial_pack_sha1,
			 off_t partial_pack_offset)
{
	int aligned_sz, buf_sz = 8 * 1024;
	git_SHA_CTX old_sha1_ctx, new_sha1_ctx;
	struct pack_header hdr;
	char *buf;

	git_SHA1_Init(&old_sha1_ctx);
	git_SHA1_Init(&new_sha1_ctx);

	if (lseek(pack_fd, 0, SEEK_SET) != 0)
		die_errno("Failed seeking to start of '%s'", pack_name);
	if (read_in_full(pack_fd, &hdr, sizeof(hdr)) != sizeof(hdr))
		die_errno("Unable to reread header of '%s'", pack_name);
	if (lseek(pack_fd, 0, SEEK_SET) != 0)
		die_errno("Failed seeking to start of '%s'", pack_name);
	git_SHA1_Update(&old_sha1_ctx, &hdr, sizeof(hdr));
	hdr.hdr_entries = htonl(object_count);
	git_SHA1_Update(&new_sha1_ctx, &hdr, sizeof(hdr));
	write_or_die(pack_fd, &hdr, sizeof(hdr));
	partial_pack_offset -= sizeof(hdr);

	buf = xmalloc(buf_sz);
	aligned_sz = buf_sz - sizeof(hdr);
	for (;;) {
		ssize_t m, n;
		m = (partial_pack_sha1 && partial_pack_offset < aligned_sz) ?
			partial_pack_offset : aligned_sz;
		n = xread(pack_fd, buf, m);
		if (!n)
			break;
		if (n < 0)
			die_errno("Failed to checksum '%s'", pack_name);
		git_SHA1_Update(&new_sha1_ctx, buf, n);

		aligned_sz -= n;
		if (!aligned_sz)
			aligned_sz = buf_sz;

		if (!partial_pack_sha1)
			continue;

		git_SHA1_Update(&old_sha1_ctx, buf, n);
		partial_pack_offset -= n;
		if (partial_pack_offset == 0) {
			unsigned char sha1[20];
			git_SHA1_Final(sha1, &old_sha1_ctx);
			if (hashcmp(sha1, partial_pack_sha1) != 0)
				die("Unexpected checksum for %s "
				    "(disk corruption?)", pack_name);
			/*
			 * Now let's compute the SHA1 of the remainder of the
			 * pack, which also means making partial_pack_offset
			 * big enough not to matter anymore.
			 */
			git_SHA1_Init(&old_sha1_ctx);
			partial_pack_offset = ~partial_pack_offset;
			partial_pack_offset -= MSB(partial_pack_offset, 1);
		}
	}
	free(buf);

	if (partial_pack_sha1)
		git_SHA1_Final(partial_pack_sha1, &old_sha1_ctx);
	git_SHA1_Final(new_pack_sha1, &new_sha1_ctx);
	write_or_die(pack_fd, new_pack_sha1, 20);
	fsync_or_die(pack_fd, pack_name);
}