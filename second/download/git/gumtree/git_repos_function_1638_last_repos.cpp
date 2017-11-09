static void prepare_filter_bits(void)
{
	int i;

	if (!filter_bit[DIFF_STATUS_ADDED]) {
		for (i = 0; diff_status_letters[i]; i++)
			filter_bit[(int) diff_status_letters[i]] = (1 << i);
	}
}