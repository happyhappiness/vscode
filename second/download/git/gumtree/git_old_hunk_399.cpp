	off_t to_write, total;
	int fd;

	if (!is_pack_valid(reuse_packfile))
		die("packfile is invalid: %s", reuse_packfile->pack_name);

	fd = git_open_noatime(reuse_packfile->pack_name);
	if (fd < 0)
		die_errno("unable to open packfile for reuse: %s",
			  reuse_packfile->pack_name);

	if (lseek(fd, sizeof(struct pack_header), SEEK_SET) == -1)
		die_errno("unable to seek in reused packfile");
