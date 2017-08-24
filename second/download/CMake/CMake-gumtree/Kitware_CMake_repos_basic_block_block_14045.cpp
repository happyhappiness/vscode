{
		if (n < 0) {
			/* Use a replaced unicode character. */
			n *= -1;
			ret = -1;
		}
		s += n;
		len -= n;
		while ((w = unparse(p, endp - p, uc)) == 0) {
			/* There is not enough output buffer so
			 * we have to expand it. */
			as->length = p - as->s;
			if (archive_string_ensure(as,
			    as->buffer_length + len * tm + ts) == NULL)
				return (-1);
			p = as->s + as->length;
			endp = as->s + as->buffer_length - ts;
		}
		p += w;
	}