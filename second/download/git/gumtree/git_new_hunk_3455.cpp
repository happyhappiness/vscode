
	if (mtime) {
		struct utimbuf utb;
		utb.actime = mtime;
		utb.modtime = mtime;
		if (utime(tmp_file.buf, &utb) < 0)
			warning_errno("failed utime() on %s", tmp_file.buf);
	}

	return finalize_object_file(tmp_file.buf, filename);
}

static int freshen_loose_object(const unsigned char *sha1)
