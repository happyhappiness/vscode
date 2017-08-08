{
	struct private_b64encode *state = (struct private_b64encode *)f->data;
	size_t bs = 65536, bpb;
	int ret;

	ret = __archive_write_open_filter(f->next_filter);
	if (ret != ARCHIVE_OK)
		return (ret);

	if (f->archive->magic == ARCHIVE_WRITE_MAGIC) {
		/* Buffer size should be a multiple number of the of bytes
		 * per block for performance. */
		bpb = archive_write_get_bytes_per_block(f->archive);
		if (bpb > bs)
			bs = bpb;
		else if (bpb != 0)
			bs -= bs % bpb;
	}

	state->bs = bs;
	if (archive_string_ensure(&state->encoded_buff, bs + 512) == NULL) {
		archive_set_error(f->archive, ENOMEM,
		    "Can't allocate data for b64encode buffer");
		return (ARCHIVE_FATAL);
	}

	archive_string_sprintf(&state->encoded_buff, "begin-base64 %o %s\n",
	    state->mode, state->name.s);

	f->data = state;
	return (0);
}