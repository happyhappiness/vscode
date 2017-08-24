(*p >= '0' && *p <= '9')
			data = data * 10 + *p - '0';
		else {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Invalid value for option ``%s''", key);
			return (ARCHIVE_FATAL);
		}