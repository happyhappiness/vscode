static void submit_scoreboard (char *buf, apache_t *st)
{
	/*
	 * Scoreboard Key:
	 * "_" Waiting for Connection, "S" Starting up,
	 * "R" Reading Request for apache and read-POST for lighttpd,
	 * "W" Sending Reply, "K" Keepalive (read), "D" DNS Lookup,
	 * "C" Closing connection, "L" Logging, "G" Gracefully finishing,
	 * "I" Idle cleanup of worker, "." Open slot with no current process
	 * Lighttpd specific legends -
	 * "E" hard error, "." connect, "h" handle-request,
	 * "q" request-start, "Q" request-end, "s" response-start
	 * "S" response-end, "r" read
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

	/* lighttpd specific */
	long long hard_error     = 0LL;
	long long lighttpd_read  = 0LL;
	long long handle_request = 0LL;
	long long request_start  = 0LL;
	long long request_end    = 0LL;
	long long response_start = 0LL;
	long long response_end   = 0LL;

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
		else if (buf[i] == 'r') lighttpd_read++;
		else if (buf[i] == 'h') handle_request++;
		else if (buf[i] == 'E') hard_error++;
		else if (buf[i] == 'q') request_start++;
		else if (buf[i] == 'Q') request_end++;
		else if (buf[i] == 's') response_start++;
		else if (buf[i] == 'S') response_end++;
	}

	if (st->server_type == APACHE)
	{
		submit_gauge ("apache_scoreboard", "open"     , open, st);
		submit_gauge ("apache_scoreboard", "waiting"  , waiting, st);
		submit_gauge ("apache_scoreboard", "starting" , starting, st);
		submit_gauge ("apache_scoreboard", "reading"  , reading, st);
		submit_gauge ("apache_scoreboard", "sending"  , sending, st);
		submit_gauge ("apache_scoreboard", "keepalive", keepalive, st);
		submit_gauge ("apache_scoreboard", "dnslookup", dnslookup, st);
		submit_gauge ("apache_scoreboard", "closing"  , closing, st);
		submit_gauge ("apache_scoreboard", "logging"  , logging, st);
		submit_gauge ("apache_scoreboard", "finishing", finishing, st);
		submit_gauge ("apache_scoreboard", "idle_cleanup", idle_cleanup, st);
	}
	else
	{
		submit_gauge ("apache_scoreboard", "connect"       , open, st);
		submit_gauge ("apache_scoreboard", "close"         , closing, st);
		submit_gauge ("apache_scoreboard", "hard_error"    , hard_error, st);
		submit_gauge ("apache_scoreboard", "read"          , lighttpd_read, st);
		submit_gauge ("apache_scoreboard", "read_post"     , reading, st);
		submit_gauge ("apache_scoreboard", "write"         , sending, st);
		submit_gauge ("apache_scoreboard", "handle_request", handle_request, st);
		submit_gauge ("apache_scoreboard", "request_start" , request_start, st);
		submit_gauge ("apache_scoreboard", "request_end"   , request_end, st);
		submit_gauge ("apache_scoreboard", "response_start", response_start, st);
		submit_gauge ("apache_scoreboard", "response_end"  , response_end, st);
	}
}