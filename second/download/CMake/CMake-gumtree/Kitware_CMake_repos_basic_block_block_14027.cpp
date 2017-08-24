{
		/* We have a code point that won't fit into a
		 * wchar_t; convert it to a surrogate pair. */
		if (remaining < 4)
			return (0);
		uc -= 0x10000;
		archive_be16enc(utf16, ((uc >> 10) & 0x3ff) + 0xD800);
		archive_be16enc(utf16+2, (uc & 0x3ff) + 0xDC00);
		return (4);
	}