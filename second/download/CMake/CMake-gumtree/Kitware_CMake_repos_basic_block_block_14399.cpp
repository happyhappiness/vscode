{
		if (value == NULL) {
			archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
			    "mode option requires octal digits");
			return (ARCHIVE_FAILED);
		}
		state->mode = (int)atol8(value, strlen(value)) & 0777;
		return (ARCHIVE_OK);
	}