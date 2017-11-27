static int ping_init (void)
{
	if (pingobj == NULL)
		return (-1);

	if (hosts != NULL)
		add_hosts ();

	return (0);
}