(hd->flags & NEXT_CABINET) {
		/* How many bytes are used for szCabinetNext. */
		if ((p = __archive_read_ahead(a, used+256, NULL)) == NULL)
			return (truncated_error(a));
		if ((len = cab_strnlen(p + used, 255)) <= 0)
			goto invalid;
		used += len + 1;
		/* How many bytes are used for szDiskNext. */
		if ((p = __archive_read_ahead(a, used+256, NULL)) == NULL)
			return (truncated_error(a));
		if ((len = cab_strnlen(p + used, 255)) <= 0)
			goto invalid;
		used += len + 1;
	}