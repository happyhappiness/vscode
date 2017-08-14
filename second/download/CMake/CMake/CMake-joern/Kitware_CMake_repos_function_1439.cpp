static int
lzip_tail(struct archive_read_filter *self)
{
	struct private_data *state;
	const unsigned char *f;
	ssize_t avail_in;
	int tail;

	state = (struct private_data *)self->data;
	if (state->lzip_ver == 0)
		tail = 12;
	else
		tail = 20;
	f = __archive_read_filter_ahead(self->upstream, tail, &avail_in);
	if (f == NULL && avail_in < 0)
		return (ARCHIVE_FATAL);
	if (f == NULL || avail_in < tail) {
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "Lzip: Remaining data is less bytes");
		return (ARCHIVE_FAILED);
	}

	/* Check the crc32 value of the uncompressed data of the current
	 * member */
	if (state->crc32 != archive_le32dec(f)) {
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "Lzip: CRC32 error");
		return (ARCHIVE_FAILED);
	}

	/* Check the uncompressed size of the current member */
	if ((uint64_t)state->member_out != archive_le64dec(f + 4)) {
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "Lzip: Uncompressed size error");
		return (ARCHIVE_FAILED);
	}

	/* Check the total size of the current member */
	if (state->lzip_ver == 1 &&
	    (uint64_t)state->member_in + tail != archive_le64dec(f + 12)) {
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "Lzip: Member size error");
		return (ARCHIVE_FAILED);
	}
	__archive_read_filter_consume(self->upstream, tail);

	/* If current lzip data consists of multi member, try decompressing
	 * a next member. */
	if (lzip_has_member(self->upstream) != 0) {
		state->in_stream = 0;
		state->crc32 = 0;
		state->member_out = 0;
		state->member_in = 0;
		state->eof = 0;
	}
	return (ARCHIVE_OK);
}