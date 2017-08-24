(len == 1) {
			archive_strappend_char(as, base64[c]);
			archive_strappend_char(as, '=');
			archive_strappend_char(as, '=');
		} else {
			c |= (p[1] & 0xf0) >> 4;
			archive_strappend_char(as, base64[c]);
			c = (p[1] & 0x0f) << 2;
			archive_strappend_char(as, base64[c]);
			archive_strappend_char(as, '=');
		}