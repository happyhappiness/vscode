((c ^ neg) & 0x80) {
		return neg ? INT64_MIN : INT64_MAX;
	}