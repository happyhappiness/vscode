{
	struct group	*result;
	(void)cache; /* UNUSED */

	result = getgrgid((gid_t)id);

	if (result == NULL)
		return (NULL);

	return strdup(result->gr_name);
}