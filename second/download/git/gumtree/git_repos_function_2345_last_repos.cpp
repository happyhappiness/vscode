void attr_check_clear(struct attr_check *check)
{
	FREE_AND_NULL(check->items);
	check->alloc = 0;
	check->nr = 0;

	FREE_AND_NULL(check->all_attrs);
	check->all_attrs_nr = 0;

	drop_attr_stack(&check->stack);
}