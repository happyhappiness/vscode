static void aprerr(const char *fn, apr_status_t rv)
{
    char buf[120];

    fprintf(stderr, "%s->%d/%s\n",
            fn, rv, apr_strerror(rv, buf, sizeof buf));
    exit(1);
}