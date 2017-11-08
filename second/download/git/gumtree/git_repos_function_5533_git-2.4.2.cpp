static DWORD WINAPI console_thread(LPVOID unused)
{
	unsigned char buffer[BUFFER_SIZE];
	DWORD bytes;
	int start, end = 0, c, parampos = 0, state = TEXT;
	int params[MAX_PARAMS];

	while (1) {
		/* read next chunk of bytes from the pipe */
		if (!ReadFile(hread, buffer + end, BUFFER_SIZE - end, &bytes,
				NULL)) {
			/* exit if pipe has been closed or disconnected */
			if (GetLastError() == ERROR_PIPE_NOT_CONNECTED ||
					GetLastError() == ERROR_BROKEN_PIPE)
				break;
			/* ignore other errors */
			continue;
		}

		/* scan the bytes and handle ANSI control codes */
		bytes += end;
		start = end = 0;
		while (end < bytes) {
			c = buffer[end++];
			switch (state) {
			case TEXT:
				if (c == ESCAPE) {
					/* print text seen so far */
					if (end - 1 > start)
						write_console(buffer + start,
							end - 1 - start);

					/* then start parsing escape sequence */
					start = end - 1;
					memset(params, 0, sizeof(params));
					parampos = 0;
					state = ESCAPE;
				}
				break;

			case ESCAPE:
				/* continue if "\033[", otherwise bail out */
				state = (c == BRACKET) ? BRACKET : TEXT;
				break;

			case BRACKET:
				/* parse [0-9;]* into array of parameters */
				if (c >= '0' && c <= '9') {
					params[parampos] *= 10;
					params[parampos] += c - '0';
				} else if (c == ';') {
					/*
					 * next parameter, bail out if out of
					 * bounds
					 */
					parampos++;
					if (parampos >= MAX_PARAMS)
						state = TEXT;
				} else {
					/*
					 * end of escape sequence, change
					 * console attributes
					 */
					set_attr(c, params, parampos + 1);
					start = end;
					state = TEXT;
				}
				break;
			}
		}

		/* print remaining text unless parsing an escape sequence */
		if (state == TEXT && end > start) {
			/* check for incomplete UTF-8 sequences and fix end */
			if (buffer[end - 1] >= 0x80) {
				if (buffer[end -1] >= 0xc0)
					end--;
				else if (end - 1 > start &&
						buffer[end - 2] >= 0xe0)
					end -= 2;
				else if (end - 2 > start &&
						buffer[end - 3] >= 0xf0)
					end -= 3;
			}

			/* print remaining complete UTF-8 sequences */
			if (end > start)
				write_console(buffer + start, end - start);

			/* move remaining bytes to the front */
			if (end < bytes)
				memmove(buffer, buffer + end, bytes - end);
			end = bytes - end;
		} else {
			/* all data has been consumed, mark buffer empty */
			end = 0;
		}
	}

	/* check if the console font supports unicode */
	warn_if_raster_font();

	CloseHandle(hread);
	return 0;
}