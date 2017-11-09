static int macroexpand_one(struct all_attrs_item *all_attrs, int nr, int rem)
{
	const struct all_attrs_item *item = &all_attrs[nr];

	if (item->macro && item->value == ATTR__TRUE)
		return fill_one("expand", all_attrs, item->macro, rem);
	else
		return rem;
}