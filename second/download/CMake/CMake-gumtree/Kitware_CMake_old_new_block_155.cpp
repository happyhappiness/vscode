{
		/* nawww, I wish they promised backward compatibility
		 * anyhoo, in their infinite wisdom the 28500 guys might
		 * come up with something we can't possibly handle so
		 * best end things here */
		archive_set_error(
			&a->archive, ARCHIVE_ERRNO_MISC,
			"Unsupported record version");
		return (ARCHIVE_FATAL);
	}