{
		sign = -1;
		limit = ((uint64_t)(INT64_MAX) + 1) / base;
		last_digit_limit = ((uint64_t)(INT64_MAX) + 1) % base;
		++(*p);
	}