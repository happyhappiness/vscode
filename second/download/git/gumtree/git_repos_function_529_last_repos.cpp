static int find_renames(struct diff_score *mx, int dst_cnt, int minimum_score, int copies)
{
	int count = 0, i;

	for (i = 0; i < dst_cnt * NUM_CANDIDATE_PER_DST; i++) {
		struct diff_rename_dst *dst;

		if ((mx[i].dst < 0) ||
		    (mx[i].score < minimum_score))
			break; /* there is no more usable pair. */
		dst = &rename_dst[mx[i].dst];
		if (dst->pair)
			continue; /* already done, either exact or fuzzy. */
		if (!copies && rename_src[mx[i].src].p->one->rename_used)
			continue;
		record_rename_pair(mx[i].dst, mx[i].src, mx[i].score);
		count++;
	}
	return count;
}