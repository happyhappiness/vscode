static int give_context(struct sline *sline, unsigned long cnt, int num_parent)
{
	unsigned long all_mask = (1UL<<num_parent) - 1;
	unsigned long mark = (1UL<<num_parent);
	unsigned long no_pre_delete = (2UL<<num_parent);
	unsigned long i;

	/* Two groups of interesting lines may have a short gap of
	 * uninteresting lines.  Connect such groups to give them a
	 * bit of context.
	 *
	 * We first start from what the interesting() function says,
	 * and mark them with "mark", and paint context lines with the
	 * mark.  So interesting() would still say false for such context
	 * lines but they are treated as "interesting" in the end.
	 */
	i = find_next(sline, mark, 0, cnt, 0);
	if (cnt < i)
		return 0;

	while (i <= cnt) {
		unsigned long j = (context < i) ? (i - context) : 0;
		unsigned long k;

		/* Paint a few lines before the first interesting line. */
		while (j < i) {
			if (!(sline[j].flag & mark))
				sline[j].flag |= no_pre_delete;
			sline[j++].flag |= mark;
		}

	again:
		/* we know up to i is to be included.  where does the
		 * next uninteresting one start?
		 */
		j = find_next(sline, mark, i, cnt, 1);
		if (cnt < j)
			break; /* the rest are all interesting */

		/* lookahead context lines */
		k = find_next(sline, mark, j, cnt, 0);
		j = adjust_hunk_tail(sline, all_mask, i, j);

		if (k < j + context) {
			/* k is interesting and [j,k) are not, but
			 * paint them interesting because the gap is small.
			 */
			while (j < k)
				sline[j++].flag |= mark;
			i = k;
			goto again;
		}

		/* j is the first uninteresting line and there is
		 * no overlap beyond it within context lines.  Paint
		 * the trailing edge a bit.
		 */
		i = k;
		k = (j + context < cnt+1) ? j + context : cnt+1;
		while (j < k)
			sline[j++].flag |= mark;
	}
	return 1;
}