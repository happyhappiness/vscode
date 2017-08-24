{
			if (l>limit || (l == limit && digit > last_digit_limit)) {
				return maxval; /* Truncate on overflow. */
			}
			l = (l * base) + digit;
			digit = *++p - '0';
			char_cnt--;
		}