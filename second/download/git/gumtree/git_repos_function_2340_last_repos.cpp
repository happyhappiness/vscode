struct attr_check *attr_check_alloc(void)
{
	struct attr_check *c = xcalloc(1, sizeof(struct attr_check));

	/* save pointer to the check struct */
	check_vector_add(c);

	return c;
}