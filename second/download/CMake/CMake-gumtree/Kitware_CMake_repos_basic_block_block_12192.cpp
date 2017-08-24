(p[len-nl-1] != '\\') {
				if (multiline == 1 &&
				    ++entry_cnt >= MAX_BID_ENTRY)
					break;
				multiline = 0;
			}