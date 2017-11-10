static off_t write_reused_pack(struct sha1file *f)
{
	unsigned char buffer[8192];
	off_t to_write, total;
	int fd;

	if (!is_pack_valid(reuse_packfile))
		die("packfile is invalid: %s", reuse_packfile->pack_name);

	fd = git_open(reuse_packfile->pack_name);
	if (fd < 0)
		die_errno("unable to open packfile for reuse: %s",
			  reuse_packfile->pack_name);

	if (lseek(fd, sizeof(struct pack_header), SEEK_SET) == -1)
		die_errno("unable to seek in reused packfile");

	if (reuse_packfile_offset < 0)
		reuse_packfile_offset = reuse_packfile->pack_size - 20;

	total = to_write = reuse_packfile_offset - sizeof(struct pack_header);

	while (to_write) {
		int read_pack = xread(fd, buffer, sizeof(buffer));

		if (read_pack <= 0)
			die_errno("unable to read from reused packfile");

		if (read_pack > to_write)
			read_pack = to_write;

		sha1write(f, buffer, read_pack);
		to_write -= read_pack;

		/*
		 * We don't know the actual number of objects written,
		 * only how many bytes written, how many bytes total, and
		 * how many objects total. So we can fake it by pretending all
		 * objects we are writing are the same size. This gives us a
		 * smooth progress meter, and at the end it matches the true
		 * answer.
		 */
		written = reuse_packfile_objects *
				(((double)(total - to_write)) / total);
		display_progress(progress_state, written);
	}

	close(fd);
	written = reuse_packfile_objects;
	display_progress(progress_state, written);
	return reuse_packfile_offset - sizeof(struct pack_header);
}