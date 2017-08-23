static ssize_t
rpm_filter_read(struct archive_read_filter *self, const void **buff)
{
	struct rpm *rpm;
	const unsigned char *b;
	ssize_t avail_in, total;
	size_t used, n;
	uint32_t section;
	uint32_t bytes;

	rpm = (struct rpm *)self->data;
	*buff = NULL;
	total = avail_in = 0;
	b = NULL;
	used = 0;
	do {
		if (b == NULL) {
			b = __archive_read_filter_ahead(self->upstream, 1,
			    &avail_in);
			if (b == NULL) {
				if (avail_in < 0)
					return (ARCHIVE_FATAL);
				else
					break;
			}
		}

		switch (rpm->state) {
		case ST_LEAD:
			if (rpm->total_in + avail_in < RPM_LEAD_SIZE)
				used += avail_in;
			else {
				n = (size_t)(RPM_LEAD_SIZE - rpm->total_in);
				used += n;
				b += n;
				rpm->state = ST_HEADER;
				rpm->hpos = 0;
				rpm->hlen = 0;
				rpm->first_header = 1;
			}
			break;
		case ST_HEADER:
			n = 16 - rpm->hpos;
			if (n > avail_in - used)
				n = avail_in - used;
			memcpy(rpm->header+rpm->hpos, b, n);
			b += n;
			used += n;
			rpm->hpos += n;

			if (rpm->hpos == 16) {
				if (rpm->header[0] != 0x8e ||
				    rpm->header[1] != 0xad ||
				    rpm->header[2] != 0xe8 ||
				    rpm->header[3] != 0x01) {
					if (rpm->first_header) {
						archive_set_error(
						    &self->archive->archive,
						    ARCHIVE_ERRNO_FILE_FORMAT,
						    "Unrecoginized rpm header");
						return (ARCHIVE_FATAL);
					}
					rpm->state = ST_ARCHIVE;
					*buff = rpm->header;
					total = rpm->hpos;
					break;
				}
				/* Calculate 'Header' length. */
				section = archive_be32dec(rpm->header+8);
				bytes = archive_be32dec(rpm->header+12);
				rpm->hlen = 16 + section * 16 + bytes;
				rpm->state = ST_HEADER_DATA;
				rpm->first_header = 0;
			}
			break;
		case ST_HEADER_DATA:
			n = rpm->hlen - rpm->hpos;
			if (n > avail_in - used)
				n = avail_in - used;
			b += n;
			used += n;
			rpm->hpos += n;
			if (rpm->hpos == rpm->hlen)
				rpm->state = ST_PADDING;
			break;
		case ST_PADDING:
			while (used < (size_t)avail_in) {
				if (*b != 0) {
					/* Read next header. */
					rpm->state = ST_HEADER;
					rpm->hpos = 0;
					rpm->hlen = 0;
					break;
				}
				b++;
				used++;
			}
			break;
		case ST_ARCHIVE:
			*buff = b;
			total = avail_in;
			used = avail_in;
			break;
		}
		if (used == (size_t)avail_in) {
			rpm->total_in += used;
			__archive_read_filter_consume(self->upstream, used);
			b = NULL;
			used = 0;
		}
	} while (total == 0 && avail_in > 0);

	if (used > 0 && b != NULL) {
		rpm->total_in += used;
		__archive_read_filter_consume(self->upstream, used);
	}
	return (total);
}