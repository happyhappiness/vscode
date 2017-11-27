
	return (0);
}

/* Get and print status from apcupsd NIS server */
static int apc_query_server (char *host, int port,
		struct apc_detail_s *apcups_detail)
{
	int     n;
	char    recvline[1024];
	char   *tokptr;
	char   *toksaveptr;
	char   *key;
	double  value;
	_Bool retry = 1;
	int status;

#if APCMAIN
# define PRINT_VALUE(name, val) printf("  Found property: name = %s; value = %f;\n", name, val)
#else
