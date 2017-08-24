(*p >= '0' && *p <= '9') {
		digit = *p - '0';
		if (s > limit ||
		    (s == limit && digit > last_digit_limit)) {
			s = INT64_MAX;
			break;
		}
		s = (s * 10) + digit;
		++p;
	}