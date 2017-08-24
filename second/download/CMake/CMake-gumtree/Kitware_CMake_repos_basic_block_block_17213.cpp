{
		/* Store in two pieces, splitting at a '/'. */
		p = strchr(pp + copy_length - USTAR_name_size - 1, '/');
		/*
		 * Look for the next '/' if we chose the first character
		 * as the separator.  (ustar format doesn't permit
		 * an empty prefix.)
		 */
		if (p == pp)
			p = strchr(p + 1, '/');
		/* Fail if the name won't fit. */
		if (!p) {
			/* No separator. */
			archive_set_error(&a->archive, ENAMETOOLONG,
			    "Pathname too long");
			ret = ARCHIVE_FAILED;
		} else if (p[1] == '\0') {
			/*
			 * The only feasible separator is a final '/';
			 * this would result in a non-empty prefix and
			 * an empty name, which POSIX doesn't
			 * explicitly forbid, but it just feels wrong.
			 */
			archive_set_error(&a->archive, ENAMETOOLONG,
			    "Pathname too long");
			ret = ARCHIVE_FAILED;
		} else if (p  > pp + USTAR_prefix_size) {
			/* Prefix is too long. */
			archive_set_error(&a->archive, ENAMETOOLONG,
			    "Pathname too long");
			ret = ARCHIVE_FAILED;
		} else {
			/* Copy prefix and remainder to appropriate places */
			memcpy(h + USTAR_prefix_offset, pp, p - pp);
			memcpy(h + USTAR_name_offset, p + 1,
			    pp + copy_length - p - 1);
		}
	}