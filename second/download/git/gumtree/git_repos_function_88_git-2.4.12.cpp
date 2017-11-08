static int needs_rfc2047_encoding(const char *line, int len,
				  enum rfc2047_type type)
{
	int i;

	for (i = 0; i < len; i++) {
		int ch = line[i];
		if (non_ascii(ch) || ch == '\n')
			return 1;
		if ((i + 1 < len) && (ch == '=' && line[i+1] == '?'))
			return 1;
	}

	return 0;
}