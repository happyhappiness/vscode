static int get_entry_index(const struct string_list *list, const char *string,
		int *exact_match)
{
	int left = -1, right = list->nr;
	compare_strings_fn cmp = list->cmp ? list->cmp : strcmp;

	while (left + 1 < right) {
		int middle = (left + right) / 2;
		int compare = cmp(string, list->items[middle].string);
		if (compare < 0)
			right = middle;
		else if (compare > 0)
			left = middle;
		else {
			*exact_match = 1;
			return middle;
		}
	}

	*exact_match = 0;
	return right;
}