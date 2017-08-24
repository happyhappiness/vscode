(*p == *key) {
			--len;
			++p;
			++key;
			++match_len;
			continue;
		}