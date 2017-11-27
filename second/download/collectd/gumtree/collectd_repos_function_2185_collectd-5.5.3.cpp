ignorelist_t *ignorelist_create (int invert)
{
	ignorelist_t *il;

	il = malloc (sizeof (*il));
	if (il == NULL)
		return NULL;
	memset (il, 0, sizeof (*il));

	/*
	 * ->ignore == 0  =>  collect
	 * ->ignore == 1  =>  ignore
	 */
	il->ignore = invert ? 0 : 1;

	return (il);
}