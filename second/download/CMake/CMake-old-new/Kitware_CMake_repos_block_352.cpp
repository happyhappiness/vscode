{
						fsobj_error(a_eno, a_estr,
						    ARCHIVE_ERRNO_MISC,
						    "Path contains ", "'..'");
						return (ARCHIVE_FAILED);
					}