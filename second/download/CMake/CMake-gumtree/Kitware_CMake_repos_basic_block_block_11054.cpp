(l > limit || (l == limit && digit > last_digit_limit)) {
			l = UINT64_MAX; /* Truncate on overflow. */
			break;
		}