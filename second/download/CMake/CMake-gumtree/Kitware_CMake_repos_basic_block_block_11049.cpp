(p = ar->strtab; p < ar->strtab + size - 1; ++p) {
		if (*p == '/') {
			*p++ = '\0';
			if (*p != '\n')
				goto bad_string_table;
			*p = '\0';
		}
	}