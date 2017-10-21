		/* We convert this manually because we may need %lld precision,
		 * and that's not a portable sprintf() escape. */
		char buf[128], *s = buf + sizeof buf - 1;
		OFF_T num = size;
		*s = '\0';
		while (num) {
			*--s = (char)(num % 10) + '0';
			num /= 10;
		}
		if (!(*size_arg = strdup(s)))
			out_of_memory("parse_size_arg");
	}
	return size;
