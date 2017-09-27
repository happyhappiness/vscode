        s, apr_strerror(rv, buf, sizeof buf), rv);
    if (done)
        printf("Total of %d requests completed\n" , done);
    exit(rv);
}

static void set_polled_events(struct connection *c, apr_int16_t new_reqevents)
{
    apr_status_t rv;

    if (c->pollfd.reqevents != new_reqevents) {
        if (c->pollfd.reqevents != 0) {
