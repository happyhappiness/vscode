int main (int argc, char **argv)
{
	/* we are not really going to use this */
	struct apc_detail_s apcups_detail;

	openlog ("apcups", LOG_PID | LOG_NDELAY | LOG_LOCAL1, LOG_USER);

	if (global_host == NULL || strcmp (global_host, "0.0.0.0") == 0)
		global_host = "localhost";

	if(apc_query_server (global_host, global_port, &apcups_detail) < 0)
	{
		printf("apcups: Failed...\n");
		return(-1);
	}

	return 0;
}