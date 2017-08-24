{
		ws = write(zip->temp_fd, p, s);
		if (ws < 0) {
			archive_set_error(&(a->archive), errno,
			    "fwrite function failed");
			return (ARCHIVE_FATAL);
		}
		s -= ws;
		p += ws;
		zip->temp_offset += ws;
	}