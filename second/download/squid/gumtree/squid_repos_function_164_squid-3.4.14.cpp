void
usage(void)
{
    fprintf(stderr, "usage: %s: -p port -h host -n max\n", progname);
    fprintf(stderr, " -t <tracefile>  Save request trace\n");
    fprintf(stderr, " -c              Check checksum agains trace\n");
    fprintf(stderr, " -i              Send random If-Modified-Since times\n");
    fprintf(stderr, " -l <seconds>    Connection lifetime timeout (default 60)\n");
    fprintf(stderr, " -a              Accelerator mode\n");
    fprintf(stderr, " -H <string>     Custom header\n");
}