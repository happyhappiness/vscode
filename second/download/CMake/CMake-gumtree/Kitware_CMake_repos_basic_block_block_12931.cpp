(bytes_read > 0) {
		if (*p == '\n')
			return (l);
		if (*p < '0' || *p >= '0' + base)
			return (ARCHIVE_WARN);
		digit = *p - '0';
		if (l > limit || (l == limit && digit > last_digit_limit))
			l = INT64_MAX; /* Truncate on overflow. */
		else
			l = (l * base) + digit;
		p++;
		bytes_read--;
	}