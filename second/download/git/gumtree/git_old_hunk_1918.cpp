				mi = (nr - 1) * (miv - lov) / (hiv - lov);
				if (lo <= mi && mi < hi)
					break;
				die("BUG: assertion failed in binary search");
			}
		}
		if (18 <= ofs)
			die("cannot happen -- lo and hi are identical");
	}

	do {
		int cmp;
		cmp = hashcmp(fn(mi, table), sha1);
		if (!cmp)
