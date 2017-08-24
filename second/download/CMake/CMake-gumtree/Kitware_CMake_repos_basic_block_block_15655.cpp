{
		ret = __archive_write_output(a, p, strlen(p));
		if (ret != ARCHIVE_OK) {
			ret_final = ARCHIVE_FATAL;
			goto exit_write_header;
		}
	}