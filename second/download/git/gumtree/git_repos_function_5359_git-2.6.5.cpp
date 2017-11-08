static struct pll * get_permutations(struct pack_list *list, int n)
{
	struct pll *subset, *ret = NULL, *new_pll = NULL;

	if (list == NULL || pack_list_size(list) < n || n == 0)
		return NULL;

	if (n == 1) {
		while (list) {
			new_pll = xmalloc(sizeof(*new_pll));
			new_pll->pl = NULL;
			pack_list_insert(&new_pll->pl, list);
			new_pll->next = ret;
			ret = new_pll;
			list = list->next;
		}
		return ret;
	}

	while (list->next) {
		subset = get_permutations(list->next, n - 1);
		while (subset) {
			new_pll = xmalloc(sizeof(*new_pll));
			new_pll->pl = subset->pl;
			pack_list_insert(&new_pll->pl, list);
			new_pll->next = ret;
			ret = new_pll;
			subset = subset->next;
		}
		list = list->next;
	}
	return ret;
}