static void submit_scoreboard (char *buf)
{
	/*
	 * Scoreboard Key:
	 * "_" Waiting for Connection, "S" Starting up, "R" Reading Request,
	 * "W" Sending Reply, "K" Keepalive (read), "D" DNS Lookup,
	 * "C" Closing connection, "L" Logging, "G" Gracefully finishing,
	 * "I" Idle cleanup of worker, "." Open slot with no current process
	 */
	long long open      = 0LL;
	long long waiting   = 0LL;
	long long starting  = 0LL;
	long long reading   = 0LL;
	long long sending   = 0LL;
	long long keepalive = 0LL;
	long long dnslookup = 0LL;
	long long closing   = 0LL;
	long long logging   = 0LL;
	long long finishing = 0LL;
	long long idle_cleanup = 0LL;

	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '.') open++;
		else if (buf[i] == '_') waiting++;
		else if (buf[i] == 'S') starting++;
		else if (buf[i] == 'R') reading++;
		else if (buf[i] == 'W') sending++;
		else if (buf[i] == 'K') keepalive++;
		else if (buf[i] == 'D') dnslookup++;
		else if (buf[i] == 'C') closing++;
		else if (buf[i] == 'L') logging++;
		else if (buf[i] == 'G') finishing++;
		else if (buf[i] == 'I') idle_cleanup++;
	}

	submit_gauge ("apache_scoreboard", "open"     , open);
	submit_gauge ("apache_scoreboard", "waiting"  , waiting);
	submit_gauge ("apache_scoreboard", "starting" , starting);
	submit_gauge ("apache_scoreboard", "reading"  , reading);
	submit_gauge ("apache_scoreboard", "sending"  , sending);
	submit_gauge ("apache_scoreboard", "keepalive", keepalive);
	submit_gauge ("apache_scoreboard", "dnslookup", dnslookup);
	submit_gauge ("apache_scoreboard", "closing"  , closing);
	submit_gauge ("apache_scoreboard", "logging"  , logging);
	submit_gauge ("apache_scoreboard", "finishing", finishing);
	submit_gauge ("apache_scoreboard", "idle_cleanup", idle_cleanup);
}