{
		/*
		 * "C" locale special process.
		 */
		wchar_t *ws;
		const unsigned char *mp;

		if (NULL == archive_wstring_ensure(dest,
		    dest->length + length + 1))
			return (-1);

		ws = dest->s + dest->length;
		mp = (const unsigned char *)s;
		count = 0;
		while (count < (int)length && *mp) {
			*ws++ = (wchar_t)*mp++;
			count++;
		}
	}