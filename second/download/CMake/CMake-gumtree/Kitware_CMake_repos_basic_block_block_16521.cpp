{
		size_t rsize;
		ssize_t i, rs;

		if (size > (int64_t)sizeof(buff))
			rsize = sizeof(buff);
		else
			rsize = (size_t)size;

		rs = read(iso9660->temp_fd, buff, rsize);
		if (rs <= 0) {
			archive_set_error(&a->archive, errno,
			    "Can't read temporary file(%jd)",
			    (intmax_t)rs);
			return (ARCHIVE_FATAL);
		}
		for (i = 0; i < rs; i += 4)
			sum += archive_le32dec(buff + i);
		size -= rs;
	}