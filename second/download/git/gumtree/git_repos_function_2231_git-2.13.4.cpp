void attr_check_clear(struct attr_check *check)
{
	free(check->items);
	check->items = NULL;
	check->alloc = 0;
	check->nr = 0;

	free(check->all_attrs);
	check->all_attrs = NULL;
	check->all_attrs_nr = 0;

	drop_attr_stack(&check->stack);
}