				mi = (nr - 1) * (miv - lov) / (hiv - lov);
				if (lo <= mi && mi < hi)
					break;
				die("BUG: assertion failed in binary search");
			}
		}
	}

	do {
		int cmp;
		cmp = hashcmp(fn(mi, table), sha1);
		if (!cmp)
