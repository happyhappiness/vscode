			} else if (src[1] == '.') {

				if (src[2] == '/' || src[2] == '\0') {

					/* Conditionally warn about '..' */

					if (flags

					    & ARCHIVE_EXTRACT_SECURE_NODOTDOT) {

						fsobj_error(a_eno, a_estr,

						    ARCHIVE_ERRNO_MISC,

						    "Path contains ", "'..'");

						return (ARCHIVE_FAILED);

					}

				}

