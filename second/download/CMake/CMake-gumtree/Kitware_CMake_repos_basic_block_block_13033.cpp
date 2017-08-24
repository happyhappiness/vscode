(val + 8U == eol) {
		if (memcmp(val, "resource", 8U) == 0)
			return WT_RSRC;
		else if (memcmp(val, "response", 8U) == 0)
			return WT_RSP;
	}