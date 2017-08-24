(char_cnt > sizeof(int64_t)) {
		--char_cnt;
		if (c != neg)
			return neg ? INT64_MIN : INT64_MAX;
		c = *++p;
	}