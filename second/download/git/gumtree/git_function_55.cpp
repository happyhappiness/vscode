static void import_object(unsigned char *sha1, enum object_type type,
			  int raw, const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		die_errno("unable to open %s for reading", filename);

	if (!raw && type == OBJ_TREE) {
		const char *argv[] = { "mktree", NULL };
		struct child_process cmd = { argv };
		struct strbuf result = STRBUF_INIT;

		cmd.argv = argv;
		cmd.git_cmd = 1;
		cmd.in = fd;
		cmd.out = -1;

		if (start_command(&cmd))
			die("unable to spawn mktree");

		if (strbuf_read(&result, cmd.out, 41) < 0)
			die_errno("unable to read from mktree");
		close(cmd.out);

		if (finish_command(&cmd))
			die("mktree reported failure");
		if (get_sha1_hex(result.buf, sha1) < 0)
			die("mktree did not return an object name");

		strbuf_release(&result);
	} else {
		struct stat st;
		int flags = HASH_FORMAT_CHECK | HASH_WRITE_OBJECT;

		if (fstat(fd, &st) < 0)
			die_errno("unable to fstat %s", filename);
		if (index_fd(sha1, fd, &st, type, NULL, flags) < 0)
			die("unable to write object to database");
		/* index_fd close()s fd for us */
	}

	/*
	 * No need to close(fd) here; both run-command and index-fd
	 * will have done it for us.
	 */
}