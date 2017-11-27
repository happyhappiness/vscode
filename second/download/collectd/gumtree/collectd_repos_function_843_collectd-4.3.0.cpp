static void my_log (int severity, const char *msg)
{
	printf ("LOG: %i - %s\n", severity, msg);
	return;
}