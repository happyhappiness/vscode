{
		archive_strappend_char(s, hex[bin[i] >> 4]);
		archive_strappend_char(s, hex[bin[i] & 0x0f]);
	}