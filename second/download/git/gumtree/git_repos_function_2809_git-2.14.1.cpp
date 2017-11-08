static int get_reflog_recno_by_time(struct complete_reflogs *array,
	timestamp_t timestamp)
{
	int i;
	for (i = array->nr - 1; i >= 0; i--)
		if (timestamp >= array->items[i].timestamp)
			return i;
	return -1;
}