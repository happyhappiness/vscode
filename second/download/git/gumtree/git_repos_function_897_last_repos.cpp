static int commit_list_compare_by_date(const void *a, const void *b)
{
	timestamp_t a_date = ((const struct commit_list *)a)->item->date;
	timestamp_t b_date = ((const struct commit_list *)b)->item->date;
	if (a_date < b_date)
		return 1;
	if (a_date > b_date)
		return -1;
	return 0;
}