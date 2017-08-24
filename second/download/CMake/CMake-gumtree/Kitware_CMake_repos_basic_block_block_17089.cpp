{
	int64_t last_offset;
	int r;

	if (pax->sparse_tail == NULL)
		last_offset = 0;
	else {
		last_offset = pax->sparse_tail->offset +
		    pax->sparse_tail->remaining;
	}
	if (last_offset < offset) {
		/* Add a hole block. */
		r = _sparse_list_add_block(pax, last_offset,
		    offset - last_offset, 1);
		if (r != ARCHIVE_OK)
			return (r);
	}
	/* Add data block. */
	return (_sparse_list_add_block(pax, offset, length, 0));
}