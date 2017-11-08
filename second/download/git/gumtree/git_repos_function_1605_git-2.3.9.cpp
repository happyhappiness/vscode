static void report_helper(const struct string_list *list,
			  int seen_bits, int first, int last)
{
	const char *msg;
	switch (seen_bits) {
	case 0:
		msg = "no corresponding .idx or .pack";
		break;
	case 1:
		msg = "no corresponding .idx";
		break;
	case 2:
		msg = "no corresponding .pack";
		break;
	default:
		return;
	}
	for (; first < last; first++)
		report_garbage(msg, list->items[first].string);
}