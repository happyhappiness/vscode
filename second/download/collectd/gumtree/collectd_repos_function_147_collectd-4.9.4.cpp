llist_t *llist_create (void)
{
	llist_t *ret;

	ret = (llist_t *) malloc (sizeof (llist_t));
	if (ret == NULL)
		return (NULL);

	memset (ret, '\0', sizeof (llist_t));

	return (ret);
}