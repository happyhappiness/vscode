static void usage(void)
{
    fprintf(stderr, "Usage: %s [-t session_timeout] [-b dbpath] [-a]\n", program_name);
    fprintf(stderr, "	-t sessiontimeout	Idle timeout after which sessions will be forgotten\n");
    fprintf(stderr, "	-b dbpath		Path where persistent session database will be kept\n");
    fprintf(stderr, "	-a			Active mode requiring LOGIN argument to start a session\n");
}