static int fill_one(const char *what, struct all_attrs_item *all_attrs,
		    const struct match_attr *a, int rem)
{
	int i;

	for (i = a->num_attr - 1; rem > 0 && i >= 0; i--) {
		const struct git_attr *attr = a->state[i].attr;
		const char **n = &(all_attrs[attr->attr_nr].value);
		const char *v = a->state[i].setto;

		if (*n == ATTR__UNKNOWN) {
			debug_set(what,
				  a->is_macro ? a->u.attr->name : a->u.pat.pattern,
				  attr, v);
			*n = v;
			rem--;
			rem = macroexpand_one(all_attrs, attr->attr_nr, rem);
		}
	}
	return rem;
}