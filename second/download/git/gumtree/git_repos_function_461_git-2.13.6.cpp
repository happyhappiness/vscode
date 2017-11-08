static void record_if_better(struct diff_score m[], struct diff_score *o)
{
	int i, worst;

	/* find the worst one */
	worst = 0;
	for (i = 1; i < NUM_CANDIDATE_PER_DST; i++)
		if (score_compare(&m[i], &m[worst]) > 0)
			worst = i;

	/* is it better than the worst one? */
	if (score_compare(&m[worst], o) > 0)
		m[worst] = *o;
}