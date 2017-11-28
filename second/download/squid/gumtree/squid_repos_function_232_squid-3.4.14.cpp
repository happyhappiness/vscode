static void usage(void)
{
    log_error("Wrong usage. Please reconfigure in squid.conf.\n");

    fprintf(stderr, "Usage: %s [-d] [-l logfile] [-b dbpath] [-p pauselen] [-h] configfile\n", program_name);
    fprintf(stderr, "	-d            enable debugging output to logfile\n");
    fprintf(stderr, "	-l logfile    log messages to logfile\n");
    fprintf(stderr, "	-b dbpath     Path where persistent session database will be kept\n");
    fprintf(stderr, "	              If option is not used, then " DEFAULT_QUOTA_DB " will be used.\n");
    fprintf(stderr, "	-p pauselen   length in seconds to describe a pause between 2 requests.\n");
    fprintf(stderr, "	-h            show show command line help.\n");
    fprintf(stderr, "configfile is a file containing time quota definitions.\n");
}