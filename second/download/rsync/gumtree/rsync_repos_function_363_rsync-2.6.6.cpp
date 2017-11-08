static void daemon_usage(enum logcode F)
{
  print_rsync_version(F);

  rprintf(F,"\nUsage: rsync --daemon [OPTION]...\n");
  rprintf(F,"     --address=ADDRESS       bind to the specified address\n");
  rprintf(F,"     --bwlimit=KBPS          limit I/O bandwidth; KBytes per second\n");
  rprintf(F,"     --config=FILE           specify alternate rsyncd.conf file\n");
  rprintf(F,"     --no-detach             do not detach from the parent\n");
  rprintf(F,"     --port=PORT             listen on alternate port number\n");
  rprintf(F," -v, --verbose               increase verbosity\n");
#ifdef INET6
  rprintf(F," -4, --ipv4                  prefer IPv4\n");
  rprintf(F," -6, --ipv6                  prefer IPv6\n");
#endif
  rprintf(F," -h, --help                  show this help screen\n");

  rprintf(F,"\nIf you were not trying to invoke rsync as a daemon, avoid using any of the\n");
  rprintf(F,"daemon-specific rsync options.  See also the rsyncd.conf(5) man page.\n");
}