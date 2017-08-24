{
		/* How many bytes are used for szCabinetPrev. */
		if ((p = __archive_read_ahead(a, used+256, NULL)) == NULL)
			return (truncated_error(a));
		if ((len = cab_strnlen(p + used, 255)) <= 0)
			goto invalid;
		used += len + 1;
		/* How many bytes are used for szDiskPrev. */
		if ((p = __archive_read_ahead(a, used+256, NULL)) == NULL)
			return (truncated_error(a));
		if ((len = cab_strnlen(p + used, 255)) <= 0)
			goto invalid;
		used += len + 1;
	}