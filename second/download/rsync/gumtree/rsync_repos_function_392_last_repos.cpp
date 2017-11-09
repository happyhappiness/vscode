uint32 fuzzy_distance(const char *s1, unsigned len1, const char *s2, unsigned len2)
{
	uint32 a[MAXPATHLEN], diag, above, left, diag_inc, above_inc, left_inc;
	int32 cost;
	unsigned i1, i2;

	if (!len1 || !len2) {
		if (!len1) {
			s1 = s2;
			len1 = len2;
		}
		for (i1 = 0, cost = 0; i1 < len1; i1++)
			cost += s1[i1];
		return (int32)len1 * UNIT + cost;
	}

	for (i2 = 0; i2 < len2; i2++)
		a[i2] = (i2+1) * UNIT;

	for (i1 = 0; i1 < len1; i1++) {
		diag = i1 * UNIT;
		above = (i1+1) * UNIT;
		for (i2 = 0; i2 < len2; i2++) {
			left = a[i2];
			if ((cost = *((uchar*)s1+i1) - *((uchar*)s2+i2)) != 0) {
				if (cost < 0)
					cost = UNIT - cost;
				else
					cost = UNIT + cost;
			}
			diag_inc = diag + cost;
			left_inc = left + UNIT + *((uchar*)s1+i1);
			above_inc = above + UNIT + *((uchar*)s2+i2);
			a[i2] = above = left < above
			      ? (left_inc < diag_inc ? left_inc : diag_inc)
			      : (above_inc < diag_inc ? above_inc : diag_inc);
			diag = left;
		}
	}

	return a[len2-1];
}