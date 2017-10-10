		if (strbuf_read(&result, cmd.out, 41) < 0)
			die_errno("unable to read from mktree");
		close(cmd.out);

		if (finish_command(&cmd))
			die("mktree reported failure");
		if (get_oid_hex(result.buf, oid) < 0)
			die("mktree did not return an object name");

		strbuf_release(&result);
	} else {
		struct stat st;
		int flags = HASH_FORMAT_CHECK | HASH_WRITE_OBJECT;

		if (fstat(fd, &st) < 0)
			die_errno("unable to fstat %s", filename);
		if (index_fd(oid->hash, fd, &st, type, NULL, flags) < 0)
			die("unable to write object to database");
		/* index_fd close()s fd for us */
	}

	/*
	 * No need to close(fd) here; both run-command and index-fd
