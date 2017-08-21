			} else if (src[1] == '.') {
				if (src[2] == '/' || src[2] == '\0') {
					/* Conditionally warn about '..' */
					if (a->flags & ARCHIVE_EXTRACT_SECURE_NODOTDOT) {
						archive_set_error(&a->archive,
						    ARCHIVE_ERRNO_MISC,
						    "Path contains '..'");
						return (ARCHIVE_FAILED);
					}
				}
