{
	struct ar_w *ar;
	int ret;

	ar = (struct ar_w *)a->format_data;
	if (s > ar->entry_bytes_remaining)
		s = (size_t)ar->entry_bytes_remaining;

	if (ar->is_strtab > 0) {
		if (ar->has_strtab > 0) {
			archive_set_error(&a->archive, EINVAL,
			    "More than one string tables exist");
			return (ARCHIVE_WARN);
		}

		ar->strtab = (char *)malloc(s);
		if (ar->strtab == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate strtab buffer");
			return (ARCHIVE_FATAL);
		}
		strncpy(ar->strtab, buff, s);
		ar->has_strtab = 1;
	}

	ret = __archive_write_output(a, buff, s);
	if (ret != ARCHIVE_OK)
		return (ret);

	ar->entry_bytes_remaining -= s;
	return (s);
}