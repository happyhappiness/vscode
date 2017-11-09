static void wait_for_request_completion(int *done)
{
	GMainContext *mc = g_main_context_default();
	while (!*done)
		g_main_context_iteration(mc, TRUE);
}