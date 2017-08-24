{
		archive_strappend_char(as, '-');
		ud = (d == INTMAX_MIN) ? (uintmax_t)(INTMAX_MAX) + 1 : (uintmax_t)(-d);
	}