static int fill_one(const char *what, struct match_attr *a, int rem)
{
	struct git_attr_check *check = check_all_attr;
	int i;

	for (i = a->num_attr - 1; 0 < rem && 0 <= i; i--) {
		struct git_attr *attr = a->state[i].attr;
		const char **n = &(check[attr->attr_nr].value);
		const char *v = a->state[i].setto;

		if (*n == ATTR__UNKNOWN) {
			debug_set(what,
				  a->is_macro ? a->u.attr->name : a->u.pat.pattern,
				  attr, v);
			*n = v;
			rem--;
			rem = macroexpand_one(attr->attr_nr, rem);
		}
	}
	return rem;
}