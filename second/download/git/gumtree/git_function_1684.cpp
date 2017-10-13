int sha1_pos(const unsigned char *sha1, void *table, size_t nr,
	     sha1_access_fn fn)
{
	size_t hi = nr;
	size_t lo = 0;
	size_t mi = 0;

	if (!nr)
		return -1;

	if (nr != 1) {
		size_t lov, hiv, miv, ofs;

		for (ofs = 0; ofs < 18; ofs += 2) {
			lov = take2(fn(0, table) + ofs);
			hiv = take2(fn(nr - 1, table) + ofs);
			miv = take2(sha1 + ofs);
			if (miv < lov)
				return -1;
			if (hiv < miv)
				return -1 - nr;
			if (lov != hiv) {
				/*
				 * At this point miv could be equal
				 * to hiv (but sha1 could still be higher);
				 * the invariant of (mi < hi) should be
				 * kept.
				 */
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
			return mi;
		if (cmp > 0)
			hi = mi;
		else
			lo = mi + 1;
		mi = (hi + lo) / 2;
	} while (lo < hi);
	return -lo-1;
}