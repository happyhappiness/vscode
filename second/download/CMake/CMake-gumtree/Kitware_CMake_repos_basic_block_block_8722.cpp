{
	const char *s = p;

	archive_string_empty(as);

	/* Skip beginning space characters. */
	while (*s != '\0' && *s == ' ')
		s++;
	/* Copy non-space characters. */
	while (*s != '\0' && *s != ' ') {
		if (*s == '\\') {
			if (s[1] != '\0') {
				archive_strappend_char(as, s[1]);
				s += 2;
			} else {
				s++;/* Ignore this character.*/
				break;
			}
		} else if (*s == '"') {
			ssize_t q = extract_quotation(as, s);
			if (q < 0)
				return (ARCHIVE_FAILED);/* Invalid sequence. */
			s += q;
		} else {
			archive_strappend_char(as, s[0]);
			s++;
		}
	}
	return ((ssize_t)(s - p));
}