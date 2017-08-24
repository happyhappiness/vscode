(order < PPMD7_MIN_ORDER || order > PPMD7_MAX_ORDER ||
		    msize < PPMD7_MIN_MEM_SIZE || msize > PPMD7_MAX_MEM_SIZE) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Malformed PPMd parameter");
			return (ARCHIVE_FAILED);
		}