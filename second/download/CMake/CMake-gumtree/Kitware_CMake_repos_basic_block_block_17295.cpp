{
		int rc = __archive_write_output(a, _eor, sizeof(_eor) - 1U);

		if (rc != ARCHIVE_OK) {
			return rc;
		}
	}