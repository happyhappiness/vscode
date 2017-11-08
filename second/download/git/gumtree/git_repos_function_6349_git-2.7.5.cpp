void openlog(const char *ident, int logopt, int facility)
{
	if (ms_eventlog)
		return;

	ms_eventlog = RegisterEventSourceA(NULL, ident);

	if (!ms_eventlog)
		warning("RegisterEventSource() failed: %lu", GetLastError());
}