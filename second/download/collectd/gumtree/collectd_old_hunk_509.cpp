	return 0;
} /* static int my_write (data_set_t *, value_list_t *) */

/*
 * This function is called when plugin_log () has been used.
 */
static void my_log (int severity, const char *msg)
{
	printf ("LOG: %i - %s\n", severity, msg);
	return;
} /* static void my_log (int, const char *) */

/*
 * This function is called when plugin_dispatch_notification () has been used.
 */
static int my_notify (const notification_t *notif)
{
	char time_str[32] = "";
	struct tm *tm = NULL;

	int n = 0;

