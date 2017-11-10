void strbuf_add_wrapped_text(struct strbuf *buf,
		const char *text, int indent1, int indent2, int width)
{
	int indent, w, assume_utf8 = 1;
	const char *bol, *space, *start = text;
	size_t orig_len = buf->len;

	if (width <= 0) {
		strbuf_add_indented_text(buf, text, indent1, indent2);
		return;
	}

retry:
	bol = text;
	w = indent = indent1;
	space = NULL;
	if (indent < 0) {
		w = -indent;
		space = text;
	}

	for (;;) {
		char c;
		size_t skip;

		while ((skip = display_mode_esc_sequence_len(text)))
			text += skip;

		c = *text;
		if (!c || isspace(c)) {
			if (w <= width || !space) {
				const char *start = bol;
				if (!c && text == start)
					return;
				if (space)
					start = space;
				else
					strbuf_addchars(buf, ' ', indent);
				strbuf_add(buf, start, text - start);
				if (!c)
					return;
				space = text;
				if (c == '\t')
					w |= 0x07;
				else if (c == '\n') {
					space++;
					if (*space == '\n') {
						strbuf_addch(buf, '\n');
						goto new_line;
					}
					else if (!isalnum(*space))
						goto new_line;
					else
						strbuf_addch(buf, ' ');
				}
				w++;
				text++;
			}
			else {
new_line:
				strbuf_addch(buf, '\n');
				text = bol = space + isspace(*space);
				space = NULL;
				w = indent = indent2;
			}
			continue;
		}
		if (assume_utf8) {
			w += utf8_width(&text, NULL);
			if (!text) {
				assume_utf8 = 0;
				text = start;
				strbuf_setlen(buf, orig_len);
				goto retry;
			}
		} else {
			w++;
			text++;
		}
	}
}