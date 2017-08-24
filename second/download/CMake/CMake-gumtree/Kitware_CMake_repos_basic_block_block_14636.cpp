(len == 1) {
			archive_strappend_char(as, c?c + 0x20:'`');
			archive_strappend_char(as, '`');
			archive_strappend_char(as, '`');
		} else {
			c |= (p[1] & 0xf0) >> 4;
			archive_strappend_char(as, c?c + 0x20:'`');
			c = (p[1] & 0x0f) << 2;
			archive_strappend_char(as, c?c + 0x20:'`');
			archive_strappend_char(as, '`');
		}