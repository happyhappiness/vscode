static ssize_t
uudecode_filter_read(struct archive_read_filter *self, const void **buff)
{
	struct uudecode *uudecode;
	const unsigned char *b, *d;
	unsigned char *out;
	ssize_t avail_in, ravail;
	ssize_t used;
	ssize_t total;
	ssize_t len, llen, nl;

	uudecode = (struct uudecode *)self->data;

read_more:
	d = __archive_read_filter_ahead(self->upstream, 1, &avail_in);
	if (d == NULL && avail_in < 0)
		return (ARCHIVE_FATAL);
	/* Quiet a code analyzer; make sure avail_in must be zero
	 * when d is NULL. */
	if (d == NULL)
		avail_in = 0;
	used = 0;
	total = 0;
	out = uudecode->out_buff;
	ravail = avail_in;
	if (uudecode->in_cnt) {
		/*
		 * If there is remaining data which is saved by
		 * previous calling, use it first.
		 */
		if (ensure_in_buff_size(self, uudecode,
		    avail_in + uudecode->in_cnt) != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		memcpy(uudecode->in_buff + uudecode->in_cnt,
		    d, avail_in);
		d = uudecode->in_buff;
		avail_in += uudecode->in_cnt;
		uudecode->in_cnt = 0;
	}
	for (;used < avail_in; d += llen, used += llen) {
		int l, body;

		b = d;
		len = get_line(b, avail_in - used, &nl);
		if (len < 0) {
			/* Non-ascii character is found. */
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC,
			    "Insufficient compressed data");
			return (ARCHIVE_FATAL);
		}
		llen = len;
		if (nl == 0) {
			/*
			 * Save remaining data which does not contain
			 * NL('\n','\r').
			 */
			if (ensure_in_buff_size(self, uudecode, len)
			    != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			if (uudecode->in_buff != b)
				memmove(uudecode->in_buff, b, len);
			uudecode->in_cnt = len;
			if (total == 0) {
				/* Do not return 0; it means end-of-file.
				 * We should try to read bytes more. */
				__archive_read_filter_consume(
				    self->upstream, ravail);
				goto read_more;
			}
			break;
		}
		switch (uudecode->state) {
		default:
		case ST_FIND_HEAD:
			/* Do not read more than UUENCODE_BID_MAX_READ bytes */
			if (total + len >= UUENCODE_BID_MAX_READ) {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Invalid format data");
				return (ARCHIVE_FATAL);
			}
			if (len - nl >= 11 && memcmp(b, "begin ", 6) == 0)
				l = 6;
			else if (len - nl >= 18 &&
			    memcmp(b, "begin-base64 ", 13) == 0)
				l = 13;
			else
				l = 0;
			if (l != 0 && b[l] >= '0' && b[l] <= '7' &&
			    b[l+1] >= '0' && b[l+1] <= '7' &&
			    b[l+2] >= '0' && b[l+2] <= '7' && b[l+3] == ' ') {
				if (l == 6)
					uudecode->state = ST_READ_UU;
				else
					uudecode->state = ST_READ_BASE64;
			}
			break;
		case ST_READ_UU:
			if (total + len * 2 > OUT_BUFF_SIZE)
				break;
			body = len - nl;
			if (!uuchar[*b] || body <= 0) {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Insufficient compressed data");
				return (ARCHIVE_FATAL);
			}
			/* Get length of undecoded bytes of curent line. */
			l = UUDECODE(*b++);
			body--;
			if (l > body) {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Insufficient compressed data");
				return (ARCHIVE_FATAL);
			}
			if (l == 0) {
				uudecode->state = ST_UUEND;
				break;
			}
			while (l > 0) {
				int n = 0;

				if (l > 0) {
					if (!uuchar[b[0]] || !uuchar[b[1]])
						break;
					n = UUDECODE(*b++) << 18;
					n |= UUDECODE(*b++) << 12;
					*out++ = n >> 16; total++;
					--l;
				}
				if (l > 0) {
					if (!uuchar[b[0]])
						break;
					n |= UUDECODE(*b++) << 6;
					*out++ = (n >> 8) & 0xFF; total++;
					--l;
				}
				if (l > 0) {
					if (!uuchar[b[0]])
						break;
					n |= UUDECODE(*b++);
					*out++ = n & 0xFF; total++;
					--l;
				}
			}
			if (l) {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Insufficient compressed data");
				return (ARCHIVE_FATAL);
			}
			break;
		case ST_UUEND:
			if (len - nl == 3 && memcmp(b, "end ", 3) == 0)
				uudecode->state = ST_FIND_HEAD;
			else {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Insufficient compressed data");
				return (ARCHIVE_FATAL);
			}
			break;
		case ST_READ_BASE64:
			if (total + len * 2 > OUT_BUFF_SIZE)
				break;
			l = len - nl;
			if (l >= 3 && b[0] == '=' && b[1] == '=' &&
			    b[2] == '=') {
				uudecode->state = ST_FIND_HEAD;
				break;
			}
			while (l > 0) {
				int n = 0;

				if (l > 0) {
					if (!base64[b[0]] || !base64[b[1]])
						break;
					n = base64num[*b++] << 18;
					n |= base64num[*b++] << 12;
					*out++ = n >> 16; total++;
					l -= 2;
				}
				if (l > 0) {
					if (*b == '=')
						break;
					if (!base64[*b])
						break;
					n |= base64num[*b++] << 6;
					*out++ = (n >> 8) & 0xFF; total++;
					--l;
				}
				if (l > 0) {
					if (*b == '=')
						break;
					if (!base64[*b])
						break;
					n |= base64num[*b++];
					*out++ = n & 0xFF; total++;
					--l;
				}
			}
			if (l && *b != '=') {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Insufficient compressed data");
				return (ARCHIVE_FATAL);
			}
			break;
		}
	}

	__archive_read_filter_consume(self->upstream, ravail);

	*buff = uudecode->out_buff;
	uudecode->total += total;
	return (total);
}