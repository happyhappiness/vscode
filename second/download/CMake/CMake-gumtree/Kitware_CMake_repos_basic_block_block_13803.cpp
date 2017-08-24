(r == (size_t)-1 || r == (size_t)-2) {
			ret_val = -1;
			if (errno == EILSEQ) {
				++mbs;
				--mbs_length;
				continue;
			} else
				break;
		}