{
	const unsigned char *p = (const unsigned char *)_p;

	if (p == NULL)
		return (1);
	while (*p != '\0' && *p < 128)
		p++;
	return (*p != '\0');
}