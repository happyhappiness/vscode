{
		new_len = buf_avail;

		matches_count = 0;
		while (new_len > coder->matches[matches_count].len)
			++matches_count;

		coder->matches[matches_count++].len = new_len;
	}