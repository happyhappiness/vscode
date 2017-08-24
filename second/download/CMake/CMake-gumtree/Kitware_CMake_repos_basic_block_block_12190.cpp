{
			/* A continuance line; the terminal
			 * character of previous line was '\' character. */
			if (bid_keyword_list(p, len, 0, 0) <= 0)
				break;
			if (multiline == 1)
				detected_bytes += len;
			if (p[len-nl-1] != '\\') {
				if (multiline == 1 &&
				    ++entry_cnt >= MAX_BID_ENTRY)
					break;
				multiline = 0;
			}
			p += len;
			avail -= len;
			continue;
		}