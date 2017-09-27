        s, apr_strerror(rv, buf, sizeof buf), rv);
    if (done)
        printf("Total of %d requests completed\n" , done);
    exit(rv);
}

static void *xmalloc(size_t size)
{
    void *ret = malloc(size);
    if (ret == NULL) {
        fprintf(stderr, "Could not allocate memory (%"
                APR_SIZE_T_FMT" bytes)\n", size);
        exit(1);
    }
    return ret;
}

static void *xcalloc(size_t num, size_t size)
{
    void *ret = calloc(num, size);
    if (ret == NULL) {
        fprintf(stderr, "Could not allocate memory (%"
                APR_SIZE_T_FMT" bytes)\n", size*num);
        exit(1);
    }
    return ret;
}

static char *xstrdup(const char *s)
{
    char *ret = strdup(s);
    if (ret == NULL) {
        fprintf(stderr, "Could not allocate memory (%"
                APR_SIZE_T_FMT " bytes)\n", strlen(s));
        exit(1);
    }
    return ret;
}

/* pool abort function */
static int abort_on_oom(int retcode)
{
    fprintf(stderr, "Could not allocate memory\n");
    exit(1);
    /* not reached */
    return retcode;
}

static void set_polled_events(struct connection *c, apr_int16_t new_reqevents)
{
    apr_status_t rv;

    if (c->pollfd.reqevents != new_reqevents) {
        if (c->pollfd.reqevents != 0) {
