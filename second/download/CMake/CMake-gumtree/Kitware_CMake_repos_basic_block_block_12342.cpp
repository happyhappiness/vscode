(digit >= 0 && digit < base) {
		if (l > limit || (l == limit && digit > last_digit_limit))
			return (sign < 0) ? INT64_MIN : INT64_MAX;
		l = (l * base) + digit;
		digit = *++(*p) - '0';
	}