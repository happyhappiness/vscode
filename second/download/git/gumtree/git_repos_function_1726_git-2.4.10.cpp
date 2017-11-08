static int macroexpand_one(int nr, int rem)
{
	struct attr_stack *stk;
	struct match_attr *a = NULL;
	int i;

	if (check_all_attr[nr].value != ATTR__TRUE ||
	    !check_all_attr[nr].attr->maybe_macro)
		return rem;

	for (stk = attr_stack; !a && stk; stk = stk->prev)
		for (i = stk->num_matches - 1; !a && 0 <= i; i--) {
			struct match_attr *ma = stk->attrs[i];
			if (!ma->is_macro)
				continue;
			if (ma->u.attr->attr_nr == nr)
				a = ma;
		}

	if (a)
		rem = fill_one("expand", a, rem);

	return rem;
}