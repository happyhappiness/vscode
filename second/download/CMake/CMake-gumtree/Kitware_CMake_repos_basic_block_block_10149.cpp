(memcmp(buffer + 4, "\x31\x41\x59\x26\x53\x59", 6) == 0)
		bits_checked += 48;
	else if (memcmp(buffer + 4, "\x17\x72\x45\x38\x50\x90", 6) == 0)
		bits_checked += 48;
	else
		return (0);