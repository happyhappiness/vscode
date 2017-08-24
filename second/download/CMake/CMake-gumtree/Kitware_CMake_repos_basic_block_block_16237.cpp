{
			if (errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for UTF-16BE");
				return (ARCHIVE_FATAL);
			}
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "A filename cannot be converted to UTF-16BE;"
			    "You should disable making Joliet extension");
			ret = ARCHIVE_WARN;
		}