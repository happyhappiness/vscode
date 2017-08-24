{
	if (pathtbl->first == NULL)
		return (NULL);
	return (((struct isoent *)(void *)
		((char *)(pathtbl->last) - offsetof(struct isoent, ptnext))));
}