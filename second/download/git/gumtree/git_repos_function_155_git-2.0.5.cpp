int recv_sideband(const char *me, int in_stream, int out)
{
	unsigned pf = strlen(PREFIX);
	unsigned sf;
	char buf[LARGE_PACKET_MAX + 2*FIX_SIZE];
	char *suffix, *term;
	int skip_pf = 0;

	memcpy(buf, PREFIX, pf);
	term = getenv("TERM");
	if (isatty(2) && term && strcmp(term, "dumb"))
		suffix = ANSI_SUFFIX;
	else
		suffix = DUMB_SUFFIX;
	sf = strlen(suffix);

	while (1) {
		int band, len;
		len = packet_read(in_stream, NULL, NULL, buf + pf, LARGE_PACKET_MAX, 0);
		if (len == 0)
			break;
		if (len < 1) {
			fprintf(stderr, "%s: protocol error: no band designator\n", me);
			return SIDEBAND_PROTOCOL_ERROR;
		}
		band = buf[pf] & 0xff;
		len--;
		switch (band) {
		case 3:
			buf[pf] = ' ';
			buf[pf+1+len] = '\0';
			fprintf(stderr, "%s\n", buf);
			return SIDEBAND_REMOTE_ERROR;
		case 2:
			buf[pf] = ' ';
			do {
				char *b = buf;
				int brk = 0;

				/*
				 * If the last buffer didn't end with a line
				 * break then we should not print a prefix
				 * this time around.
				 */
				if (skip_pf) {
					b += pf+1;
				} else {
					len += pf+1;
					brk += pf+1;
				}

				/* Look for a line break. */
				for (;;) {
					brk++;
					if (brk > len) {
						brk = 0;
						break;
					}
					if (b[brk-1] == '\n' ||
					    b[brk-1] == '\r')
						break;
				}

				/*
				 * Let's insert a suffix to clear the end
				 * of the screen line if a line break was
				 * found.  Also, if we don't skip the
				 * prefix, then a non-empty string must be
				 * present too.
				 */
				if (brk > (skip_pf ? 0 : (pf+1 + 1))) {
					char save[FIX_SIZE];
					memcpy(save, b + brk, sf);
					b[brk + sf - 1] = b[brk - 1];
					memcpy(b + brk - 1, suffix, sf);
					fprintf(stderr, "%.*s", brk + sf, b);
					memcpy(b + brk, save, sf);
					len -= brk;
				} else {
					int l = brk ? brk : len;
					fprintf(stderr, "%.*s", l, b);
					len -= l;
				}

				skip_pf = !brk;
				memmove(buf + pf+1, b + brk, len);
			} while (len);
			continue;
		case 1:
			write_or_die(out, buf + pf+1, len);
			continue;
		default:
			fprintf(stderr, "%s: protocol error: bad band #%d\n",
				me, band);
			return SIDEBAND_PROTOCOL_ERROR;
		}
	}
	return 0;
}