(s = in, d = out; *s != '\0'; s++) {
		/* encode any non-printable ASCII character or '%' or '=' */
		if (*s < 33 || *s > 126 || *s == '%' || *s == '=') {
			/* URL encoding is '%' followed by two hex digits */
			*d++ = '%';
			*d++ = "0123456789ABCDEF"[0x0f & (*s >> 4)];
			*d++ = "0123456789ABCDEF"[0x0f & *s];
		} else {
			*d++ = *s;
		}
	}