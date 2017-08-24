(*p == '/') {
			*p++ = '\0';
			if (*p != '\n')
				goto bad_string_table;
			*p = '\0';
		}