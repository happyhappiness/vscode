(l > limit || (l == limit && digit > last_digit_limit))
			return (sign < 0) ? INT64_MIN : INT64_MAX;