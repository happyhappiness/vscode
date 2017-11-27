static int ping_init (void)
{
	if (hosts != NULL)
		add_hosts ();

	return (0);
}