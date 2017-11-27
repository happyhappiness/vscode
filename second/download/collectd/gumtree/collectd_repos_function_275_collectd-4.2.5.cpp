void *smalloc (size_t size)
{
	void *r;

	if ((r = malloc (size)) == NULL)
	{
		DEBUG("Not enough memory.");
		exit(3);
	}

	return r;
}