{
		size_t rsize;
		ssize_t rs;

		/* Get the current file pointer. */
		write_offset = lseek(fd, 0, SEEK_CUR);

		/* Change the file pointer to read. */
		lseek(fd, read_offset, SEEK_SET);

		rsize = rbuff_size;
		if (rsize > remaining)
			rsize = remaining;
		rs = read(iso9660->temp_fd, rbuff, rsize);
		if (rs <= 0) {
			archive_set_error(&a->archive, errno,
			    "Can't read temporary file(%jd)", (intmax_t)rs);
			ret = ARCHIVE_FATAL;
			break;
		}
		remaining -= rs;
		read_offset += rs;

		/* Put the file pointer back to write. */
		lseek(fd, write_offset, SEEK_SET);

		r = zisofs_extract(a, &zext, rbuff, rs);
		if (r < 0) {
			ret = (int)r;
			break;
		}
	}