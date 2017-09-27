static void close_connection(struct connection * c);

/* --------------------------------------------------------- */

/* simple little function to write an error string and exit */

static void err(char *s)
{
    fprintf(stderr, "%s\n", s);
    if (done)
        printf("Total of %d requests completed\n" , done);
    exit(1);
}

/* simple little function to write an APR error string and exit */

static void apr_err(char *s, apr_status_t rv)
{
    char buf[120];

    fprintf(stderr,
        "%s: %s (%d)\n",
        s, apr_strerror(rv, buf, sizeof buf), rv);
    if (done)
        printf("Total of %d requests completed\n" , done);
    exit(rv);
}

/* --------------------------------------------------------- */
/* write out request to a connection - assumes we can write
 * (small) request out in one go into our new socket buffer
 *
 */
#ifdef USE_SSL
