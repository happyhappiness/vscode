static void remove_pidfile(void)
{
	if (pidfile)
		unlink(pidfile);
}