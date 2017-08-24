(s > limit ||
		    (s == limit && digit > last_digit_limit)) {
			s = INT64_MAX;
			break;
		}