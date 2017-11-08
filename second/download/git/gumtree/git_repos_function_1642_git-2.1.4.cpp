static int macroexpand_one(int attr_nr, int rem)
{
	struct attr_stack *stk;
	struct match_attr *a = NULL;
	int i;

	if (check_all_attr[attr_nr].value != ATTR__TRUE)
		return rem;

	for (stk = attr_stack; !a && stk; stk = stk->prev)
		for (i = stk->num_matches - 1; !a && 0 <= i; i--) {
			struct match_attr *ma = stk->attrs[i];
			if (!ma->is_macro)
				continue;
			if (ma->u.attr->attr_nr == attr_nr)
				a = ma;
		}

	if (a)
		rem = fill_one("expand", a, rem);

	return rem;
}