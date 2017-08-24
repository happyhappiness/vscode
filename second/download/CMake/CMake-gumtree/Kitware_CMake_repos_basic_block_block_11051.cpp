{
		if (l>limit || (l == limit && digit > last_digit_limit)) {
			l = UINT64_MAX; /* Truncate on overflow. */
			break;
		}
		l = (l * base) + digit;
		digit = *++p - '0';
	}