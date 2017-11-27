ignorelist_t *ignorelist_create (int invert)
{
	ignorelist_t *il;

	/* smalloc exits if it failes */
	il = (ignorelist_t *) smalloc (sizeof (ignorelist_t));
	memset (il, '\0', sizeof (ignorelist_t));

	/*
	 * ->ignore == 0  =>  collect
	 * ->ignore == 1  =>  ignore
	 */
	il->ignore = invert ? 0 : 1;

	return (il);
}