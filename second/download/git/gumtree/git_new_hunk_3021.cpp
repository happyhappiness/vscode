	close_sha1_file(fd);

	if (mtime) {
		struct utimbuf utb;
		utb.actime = mtime;
		utb.modtime = mtime;
		if (utime(tmp_file.buf, &utb) < 0)
			warning("failed utime() on %s: %s",
				tmp_file.buf, strerror(errno));
	}

	return finalize_object_file(tmp_file.buf, filename);
}

static int freshen_loose_object(const unsigned char *sha1)
{
	return check_and_freshen(sha1, 1);
}
