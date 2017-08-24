(i = 0; i < size; i += 2, p += 2) {
		if (!joliet_allowed_char(p[0], p[1]))
			archive_be16enc(p, 0x005F);/* '_' */
	}