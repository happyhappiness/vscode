(rs <= 0) {
			archive_set_error(&a->archive, errno,
			    "Can't read temporary file(%jd)", (intmax_t)rs);
			ret = ARCHIVE_FATAL;
			break;
		}