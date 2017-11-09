static void report_helper(const struct string_list *list,
			  int seen_bits, int first, int last)
{
	if (seen_bits == (PACKDIR_FILE_PACK|PACKDIR_FILE_IDX))
		return;

	for (; first < last; first++)
		report_garbage(seen_bits, list->items[first].string);
}