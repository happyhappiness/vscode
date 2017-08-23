static int
read_body_to_string(struct archive_read *a, struct tar *tar,
    struct archive_string *as, const void *h, size_t *unconsumed)
{
	int64_t size;
	const struct archive_entry_header_ustar *header;
	const void *src;

	(void)tar; /* UNUSED */
	header = (const struct archive_entry_header_ustar *)h;
	size  = tar_atol(header->size, sizeof(header->size));
	if ((size > 1048576) || (size < 0)) {
		archive_set_error(&a->archive, EINVAL,
		    "Special header too large");
		return (ARCHIVE_FATAL);
	}

	/* Fail if we can't make our buffer big enough. */
	if (archive_string_ensure(as, (size_t)size+1) == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "No memory");
		return (ARCHIVE_FATAL);
	}

	tar_flush_unconsumed(a, unconsumed);

	/* Read the body into the string. */
	*unconsumed = (size_t)((size + 511) & ~ 511);
	src = __archive_read_ahead(a, *unconsumed, NULL);
	if (src == NULL) {
		*unconsumed = 0;
		return (ARCHIVE_FATAL);
	}
	memcpy(as->s, src, (size_t)size);
	as->s[size] = '\0';
	as->length = (size_t)size;
	return (ARCHIVE_OK);
}